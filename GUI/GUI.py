import tkinter as tk
import cv2
from Steering import SteeringData
from PIL import Image, ImageTk
from Buttons import Button
from MiddleMan import MiddleMan

print(1)
middleMan = MiddleMan()
print(2)

data = SteeringData()
print(3)

data.throttle = 0
print(4)

#class DummyData:
#    def __init__(self):
#        self.throttle = 0.0
#        self.steering = 0.0
#        self.throttle_gain = 0.0
#
# Create dummy data object
#data = DummyData()

# Dummy functions to replace Steering functionality
#def dummy_send_data(data):
#    print(f"[DUMMY] Sending data - Throttle: {data.throttle}, Steering: {data.steering}, Gain: {data.throttle_gain}")

buttons = Button(data, middleMan)
print(5)

#path = 0
#vid = cv2.VideoCapture(path) #Use 0 for webcam or change to your video file path

cap = cv2.VideoCapture(0)

def updateFrame():
    maybeFrame = middleMan.GetDataFromCar()
        
    if maybeFrame is not None:

        #Convert frame to RGB and resize if needed
        cv2image = cv2.cvtColor(maybeFrame, cv2.COLOR_BGR2RGB)

        scalePercentX = 45
        scalePercentY = 45

        width = int(cv2image.shape[1] * scalePercentX / 100)
        height = int(cv2image.shape[0] * scalePercentY / 100)
        cv2image = cv2.resize(cv2image, (width, height))

        pilImage = Image.fromarray(cv2image)
        
        imgtk = ImageTk.PhotoImage(image=pilImage)
        
        #Update the label with new image
        videoLabel.imgtk = imgtk
        videoLabel.configure(image=imgtk)
        
    else:
        returN, frame = cap.read()
        if returN:
            cv2image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            
            scalePercentX = 88
            scalePercentY = 67
            width = int(cv2image.shape[1] * scalePercentX / 100)
            height = int(cv2image.shape[0] * scalePercentY / 100)
            cv2image = cv2.resize(cv2image, (width, height))
            
            pilImage = Image.fromarray(cv2image)
            imgtk = ImageTk.PhotoImage(image=pilImage)
            
            videoLabel.imgtk = imgtk
            videoLabel.configure(image=imgtk)
        else:
            videoLabel.configure(bg='dark grey', width=80, height=21) #80 30
        
    
    #Schedule the next frame update
    window.after(24, updateFrame)
    



def steeringOffset(value):
    print(value)
    data.steering_offset = float(value)
    print("adjusting wheel")
    middleMan.SendDataToCar(data)

def throttleGain(value):
    data.throttle_gain = float(value)
    print("adjusting throttle gain")
    middleMan.SendDataToCar(data)   

def writeUpPressed(event):
    speed.set(float(data.throttle_gain + 0.2))
    print("adjusting throttle gain")

def writeDownPressed(event):
    speed.set(float(data.throttle_gain - 0.2))
    print("adjusting throttle gain")

def writeRightPressed(event):
    steering_.set(float(data.steering_gain + 0.1))
    data.steering_gain = data.steering_gain + 0.1
    print("adjusting wheels")

def writeLeftPressed(event):
    steering_.set(float(data.steering_gain - 0.1))
    data.steering_gain = data.steering_gain - 0.1
    print("adjusting wheels")



window = tk.Tk()
window.title('GUI')
xWindow = window.winfo_width()
yWindow = window.winfo_height()
window.geometry('1200x1200')
print(5)

videoFrame = tk.Frame(window, width=576, height=324, bg='dark grey')

videoLabel = tk.Label(videoFrame)
#videoFrame.pack_propagate(False)
videoLabel.pack(fill="both", expand=True)

#videoLabel = tk.Label(window)
#videoLabel.pack(fill="both", expand=True)

stopButton_ = tk.Button(window, text='STOP', height=4, width=10, bg="darkred",command=buttons.stopButton)
stopButton_.pack()

#runs the automatic script for the robot
autoButton_ = tk.Button(window, text='AUTO', height=4, width=10, bg="blue", command=buttons.autoButton)
autoButton_.pack()

#A slider for adjusting the wheel axle
steering_ = tk.Scale(window, from_=-1, to=1, length=300, orient= tk.HORIZONTAL, resolution=0.05,command=steeringOffset, label='SteerComponsater')
steering_.pack()

#a slider for adjusting the speed of the robot
speed = tk.Scale(window, from_=1, to=0, length=300, resolution=0.2,command=throttleGain, label='speed')
speed.pack()

#WASD button for driving manually
wButton = window.bind("<w>", buttons.writeWPressed)
wButtonR = window.bind("<KeyRelease-w>", buttons.writeWRelease)

sButton = window.bind("<s>", buttons.writeSPressed)
sButtonR = window.bind("<KeyRelease-s>", buttons.writeSRelease)

aButton = window.bind("<a>", buttons.writeAPressed)
aButton = window.bind("<KeyRelease-a>", buttons.writeARelease)

dButton = window.bind("<d>", buttons.writeDPressed)
dButton = window.bind("<KeyRelease-d>", buttons.writeDRelease)

upButton = window.bind("<Up>", writeUpPressed)

DownButton = window.bind("<Down>", writeDownPressed)

upButton = window.bind("<Right>", writeRightPressed)

DownButton = window.bind("<Left>", writeLeftPressed)

#placing every item where we want it to be
stopButton_.place(x=210, y=125) #233 125
autoButton_.place(x=210, y=200)
steering_.place(x=455, y=430)
speed.place(x=885, y=105)
videoFrame.place(x=300, y=100)
print(12)
# Start the video update loop
window.after(24, updateFrame)
middleMan.SendDataToCar(data)
window.mainloop()