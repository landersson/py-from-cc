import numpy as np

class Object:
    def __init__(self, name="Objekt"):
        self.name = name

    def initialize(self, number):
        self.number = number
        return 0

    def array_sum(self, array):
        print("Shape:", array.shape)
        print("DType:", array.dtype)
        return int(np.sum(array))

    def run(self):
        print("%s: %s" % (self.name, self.number))


