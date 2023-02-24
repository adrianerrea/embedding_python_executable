import numpy as np
from fastai.vision.all import *
from PIL import Image


def inference_function(
    input_image: bytes, height: int, width: int, depth: int, model_path: str
) -> bool:
    # Convert the data variable to a NumPy array
    data_array = np.frombuffer(input_image, dtype=np.uint8)
    data_array = data_array.reshape((height, width, int(depth)))
    img = Image.fromarray(data_array).convert("RGB")
    learn = load_learner(model_path)
    breed, _, probs = learn.predict(img)
    return breed
