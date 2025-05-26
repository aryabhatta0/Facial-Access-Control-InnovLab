import cv2

# Load pre-trained face detection model
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')

cap = cv2.VideoCapture(0)  # Use 0 for default webcam

while True:
    ret, img = cap.read()
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    
    # Detect faces
    faces = face_cascade.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=5, minSize=(30, 30))
    
    # Draw bounding boxes around detected faces
    for (x, y, w, h) in faces:
        l=25
        m=15
        cv2.rectangle(img, (x-m, y-l), (x+w+m, y+h+l), (255, 0, 0), 2)
        # cv2.rectangle(img, (x, y), (x+w, y+h), (255, 0, 0), 2)
        
        # Crop the face from the original image
        face_crop = img[y:y+h, x:x+w]        
        cv2.imshow('Cropped Face', face_crop)
        
        # Save the cropped face
        if face_crop is not None:
            filename = "cropped_face.png"
            cv2.imwrite(filename, face_crop)        
            
    cv2.imshow('Face Detection', img)
    
    #### FACE - RECOGNITION ###
    
    
    
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
