import cv2
import os

# Directory to save cropped images
output_dir = "./Data/aryabhatta_faces"
os.makedirs(output_dir, exist_ok=True)

# Load the pre-trained face detector (Haar Cascade Classifier)
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')

# Function to capture photos and crop faces
def capture_photos(num_photos, delay):
    cap = cv2.VideoCapture(0)  # Open the webcam
    count = 0

    while count < num_photos:
        ret, frame = cap.read()  # Read a frame from the webcam

        if not ret:
            print("Failed to grab a frame")
            break

        # Convert the frame to grayscale for face detection
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        # Detect faces in the frame
        faces = face_cascade.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=5, minSize=(30, 30))

        for (x, y, w, h) in faces:
            # Draw a rectangle around the detected face for visualization
            l=25
            m=15
            cv2.rectangle(frame, (x-m, y-l), (x+w+m, y+h+l), (255, 0, 0), 2)

            # Crop the detected face
            cropped_face = frame[y-l:y+h+l, x-m:x+w+m]

            # Save the cropped face
            filename = os.path.join(output_dir, f"face_{count+1}.jpg")
            cv2.imwrite(filename, cropped_face)

            count += 1

        cv2.imshow('Face Capture', frame)
        cv2.waitKey(delay)

        # Break the loop if 'q' is pressed
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    # Release the webcam and close the OpenCV windows
    cap.release()
    cv2.destroyAllWindows()


num_photos_to_capture = 10
delay_between_photos_ms = 3000  # 3 seconds
capture_photos(num_photos_to_capture, delay_between_photos_ms)
