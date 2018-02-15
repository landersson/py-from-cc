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

    def detect(self, x):
        print("Shape:", x.shape)
        print("DType:", x.dtype)

        bsz = x.shape[0]
        nd = 10
        boxes = np.ones((bsz, nd, 4), dtype=np.int32)
        probs = np.ones((bsz, nd), dtype=np.float32)
        return (boxes, probs)

    def run(self):
        print("%s: %s" % (self.name, self.number))
        return 3


