from Steering import Steering, SteeringData
import testPythonLib as tp

class Button:
    def __init__(self,
                 data,
                 steering,
                 ):
        self.steering = steering
        self.data = data



    def writeWPressed(self, event):
        if self.data.throttle == 1:
            return
        self.data.throttle = 1 * self.data.throttle_gain
        print("W pressed")
        self.steering.sendData(self.data)

    def writeWRelease(self, event):
        if self.data.throttle == 0:
            return
        self.data.throttle = float(0)
        print("W Released")
        self.steering.sendData(self.data)

    def writeSPressed(self, event):
        if self.data.throttle == -1:
            return
        self.data.throttle = -1 * self.data.throttle_gain
        print("S pressed")
        self.steering.sendData(self.data)

    def writeSRelease(self, event):
        if self.data.throttle == 0:
            return
        self.data.throttle = float(0)
        print("S Released")
        self.steering.sendData(self.data)

    def writeAPressed(self, event):            #
        if self.data.steering == 1:
            return
        self.data.steering = float(1)
        self.steering.sendData(self.data)
        print("A pressed")

    def writeARelease(self, event):
        if self.data.steering == 0:
            return
        self.data.steering = float(0)
        self.steering.sendData(self.data)
        print("A Released")

    def writeDPressed(self, event):
        if self.data.steering == -1:
            return
        self.data.steering = float(-1)
        self.steering.sendData(self.data)
        print("Depressed")

    def writeDRelease(self, event):
        if self.data.steering == 0:
            return
        self.data.steering = float(0)
        self.steering.sendData(self.data)
        print("D Released")


    def autoButton(self):
        #kjør programmet som skal kjøre automatisk
        print("Automating")

    def stopButton(self):
        self.data.throttle = float(0)
        self.data.steering = float(0)
        #automatisering = 0
        self.steering.sendData(self.data)
        print("Destroying")