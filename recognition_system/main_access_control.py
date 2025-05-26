import cv2
import torch
from dataset_utils import ImageNameDataset
from siamese_network import SiameseNetwork, ContrastiveLoss, imshow, show_plot # Import from new module
import os 
import matplotlib.pyplot as plt
import numpy as np
import random
from PIL import Image
import PIL.ImageOps

import torchvision
import torchvision.datasets as datasets
import torchvision.transforms as transforms
from torch.utils.data import DataLoader, Dataset
import torchvision.utils

from torch.autograd import Variable
import torch.nn as nn
from torch import optim
import torch.nn.functional as F
from ultralytics import YOLO

import serial 
# ser=serial.Serial('COM13',9600) # Uncomment and set correct COM port for hardware integration

# Load the YOLOv8 model
# Update this path if best.pt is moved relative to this script
model = YOLO("../models/best.pt") 

cap = cv2.VideoCapture(0)  # Use 0 for default webcam

while True:
    success, img = cap.read()

    results = model(img, verbose=False)
    res=(results[0].boxes.xyxy.tolist())
    
    # Define path for detected face image
    # This path should be accessible by the script, consider a temporary directory or a specific data folder
    detected_face_filename = "./detected_face.png" # Changed to a relative path for temporary storage

    if res:
        x, y, w, h =res[0]
        x=int(x)
        y=int(y)
        w=int(w)
        h=int(h)

        cv2.rectangle(img, (x, y), (w, h), (255, 0, 0), 2)
        face_crop = img[y:h, x:w]        
        
        if face_crop is not None:
            cv2.imwrite(detected_face_filename, face_crop)
    else:
        print("No detection")
        cv2.imshow('Face Detection', img)
        # if 'ser' in locals() and ser.is_open: # Check if serial is initialized
        #     ser.write(b'0')             # Sending '0' as a signal when no face detected
        print("Shhhhh")
        cv2.waitKey(2000)
        continue
   
    # Check if a GPU is available and set the device accordingly
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

    # Instantiate the SiameseNetwork
    siamese_model = SiameseNetwork()

    # Load the pre-trained weights
    # IMPORTANT: User needs to place 'siamese_face_cpu.pt' in the 'models/' directory
    model_weights_path = "../models/siamese_face_cpu.pt" 
    try:
        siamese_model.load_state_dict(torch.load(model_weights_path, map_location=device))
    except FileNotFoundError:
        print(f"Error: Siamese model weights not found at {model_weights_path}. Please ensure the file is in the correct location.")
        # Handle error, perhaps exit or skip recognition
        cv2.imshow('Face Detection', img)
        if cv2.waitKey(1) & 0xFF == ord('b'):
            break
        continue # Skip recognition if model weights are missing

    siamese_model.eval()
    siamese_model.to(device)

    # Define paths for known and detected faces datasets
    # These paths should be relative to the new project structure or configured appropriately
    known_images_root = "../data_preparation/known_images" # Placeholder, adjust as needed
    detected_faces_root = "./" # Detected face is saved in the same directory for now

    if os.path.exists(detected_face_filename): # Check if a face was actually detected and saved

        transformation = transforms.Compose([transforms.Resize((100,100)),transforms.ToTensor()])
        
        # Initialize datasets
        # Ensure 'known_images' directory exists and contains images for comparison
        known_dataset = ImageNameDataset(folder_path=known_images_root, transform=transformation)
        unknown_dataset = ImageNameDataset(folder_path=detected_faces_root, transform=transformation) # Use current directory for detected face

        test_dataloader1 = DataLoader(known_dataset,  batch_size=1, shuffle=True)
        test_dataloader2 = DataLoader(unknown_dataset,  batch_size=1, shuffle=True)

        names=[]
        images=[]
        distance=[]

        for data1 in test_dataloader1:
            x0,label=data1
            names.append(label[0])
            images.append(x0)
            for data2 in test_dataloader2:
                x1,_=data2
                output1, output2 = siamese_model(x0.to(device), x1.to(device))
                euclidean_distance = F.pairwise_distance(output1, output2)
                distance.append(euclidean_distance.item())
        
        min_element = min(distance)
        min_index = distance.index(min_element)
        known_image=images[min_index]
        image_name=names[min_index]

        data_iter = iter(test_dataloader2)
        unknown_image, _ = next(data_iter)
        concatenated = torch.cat((known_image, unknown_image), 0)

        # Dictionary for mapping names to signals for Arduino
        # This should ideally be loaded from a config or managed more robustly
        access_dict={"aryan":2,"tharun":3,"aryabhatta":4} 

        response_signal = 0 # Default to nothing

        if(min_element < 0.5): # Threshold for recognition
            if image_name in access_dict:
                response_signal = access_dict[image_name]
                # if 'ser' in locals() and ser.is_open:
                #     ser.write(str(response_signal).encode()) # Send signal to Arduino
                print(f"Known Person: {image_name}, Signal: {response_signal}")
                cv2.waitKey(3600) # Keep window open for a bit longer for known person
            else:
                # if 'ser' in locals() and ser.is_open:
                #     ser.write(b'1') # Send alarm signal for unrecognized known face
                print("Access Denied: Unrecognized known person")
                cv2.waitKey(600)
        else:
            # if 'ser' in locals() and ser.is_open:
            #     ser.write(b'1') # Send alarm signal for unknown person
            print("Access Denied: Unknown Person")
            cv2.waitKey(600)
        
        # Clean up the detected face image
        if os.path.exists(detected_face_filename):
            os.remove(detected_face_filename) 
            
    cv2.imshow('Face Detection', img)
    if cv2.waitKey(1) & 0xFF == ord('b'):
        break   

cap.release()
cv2.destroyAllWindows()
