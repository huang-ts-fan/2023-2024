import numpy as np
from PIL import Image
import cv2


def generate_random_image(width, height):
    # Generate random RGB values for each pixel
    random_pixels = np.random.randint(120, 140, (height, width, 3),
                                      dtype=np.uint8)

    # Create PIL image from the random pixel values
    random_image = Image.fromarray(random_pixels)

    return random_image


def generate_colour_image(width, height):
    # Generate random RGB values for each pixel
    random_pixels = np.random.randint(205, 220, (height, width, 3),
                                      dtype=np.uint8)

    # Create PIL image from the random pixel values
    random_image = Image.fromarray(random_pixels)

    return random_image


def generate_box_image(width, height, channels):
    # Generate random RGB values for each pixel
    # random_pixels = np.random.randint(205, 220, (height, width, 3),
    #                                   dtype=np.uint8)

    array = np.zeros((width, height, channels), dtype=np.uint8)

    for h in range(height):
        for w in range(height):
            for c in range(channels):
                if ((w < 20 or w > 80) or (h < 20 or h > 80)) :
                    array[h][w][c] = 255
                    pass
                else:
                    array[h][w][c] = 0
                    # if ((w < 60 or w > 40) or (h < 60 or h > 40)):
                    #     array[h][w][c] = 255

    # Create PIL image from the random pixel values
    img = Image.fromarray(array)

    return img


def generate_spotted_image(width, height, channels):

    array = np.zeros((width, height, channels), dtype=np.uint8)

    for h in range(height):
        for w in range(width):
            for c in range(3):
                if (w % 10 == 0) and (h % 10 == 0) and (w != 0) and (h != 0):
                    array[h][w][c] = 0
                    pass
                else:
                    array[h][w][c] = 255

    # Create PIL image from the random pixel values
    img = Image.fromarray(array)

    return img


def generate_lines_images(width, height, channels):
# Create a blank white image
    synth_img = np.ones((width, height), dtype=np.uint8) * 255

    # Draw horizontal lines
    cv2.line(synth_img, (0, 20), (99, 20), (0, 0, 0), 2)
    cv2.line(synth_img, (0, 40), (99, 40), (0, 0, 0), 2)
    cv2.line(synth_img, (0, 60), (99, 60), (0, 0, 0), 2)
    cv2.line(synth_img, (0, 80), (99, 80), (0, 0, 0), 2)

    # Draw vertical lines
    cv2.line(synth_img, (20, 0), (20, 99), (0, 0, 0), 2)
    cv2.line(synth_img, (40, 0), (40, 99), (0, 0, 0), 2)
    cv2.line(synth_img, (60, 0), (60, 99), (0, 0, 0), 2)
    cv2.line(synth_img, (80, 0), (80, 99), (0, 0, 0), 2)

    return synth_img
# Display the image

# Set image dimensions
width = 500
height = 500
channels = 3

# Generate random image
# random_image = generate_random_image(width, height)
new_img = generate_random_image(width, height)
# print(color_image)
# pil_image = Image.fromarray(new_img)



# Save the generated image
output_path = "advanced-programming-group-depth-first-search/tests/2D/test_images/gray500" + str(width) + ".png"
new_img.save(output_path)

# Display the generated image
new_img.show()
