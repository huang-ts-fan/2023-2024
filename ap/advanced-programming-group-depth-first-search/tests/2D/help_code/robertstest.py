import cv2
import numpy as np

# Read the input image
image = cv2.imread('advanced-programming-group-depth-first-search/tests/2D/test_images/box_image.png', cv2.IMREAD_GRAYSCALE)

# Roberts kernels
roberts_kernel_x = np.array([[1, 0], [0, -1]], dtype=np.float32)
roberts_kernel_y = np.array([[0, 1], [-1, 0]], dtype=np.float32)

# Apply Roberts edge detection along the x-axis
roberts_x = cv2.filter2D(image, -1, roberts_kernel_x)

# Apply Roberts edge detection along the y-axis
roberts_y = cv2.filter2D(image, -1, roberts_kernel_y)


roberts_x = roberts_x.astype(np.float32)
roberts_y = roberts_y.astype(np.float32)
# Combine the x and y gradient images
roberts_edges = cv2.magnitude(roberts_x, roberts_y)

# Convert edges to uint8 for display
roberts_edges = np.uint8(roberts_edges)


diff = []
for i in range(500):
    for j in range(500):
        if roberts_edges[i][j] >= 100:
            print(" Height " + str(i) + " width  " + str(j) + " value ", roberts_edges[i][j])
            # diff.append(image[i][j] - roberts_edges[i][j])



# Display the original image and the Roberts edges
cv2.imshow('Original Image', image)
cv2.imshow('Roberts Edges', roberts_edges)
cv2.waitKey(0)
cv2.destroyAllWindows()
