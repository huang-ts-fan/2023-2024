import cv2
import numpy as np

# Read the input image
image = cv2.imread('advanced-programming-group-depth-first-search/tests/2D/test_images/spotted50.png')

# Apply Sobel edge detection
edges_x = cv2.Sobel(image, cv2.CV_64F, 1, 0, ksize=3)
edges_y = cv2.Sobel(image, cv2.CV_64F, 0, 1, ksize=3)
edges = cv2.magnitude(edges_x, edges_y)

# Convert edges to uint8 for display
edges = np.uint8(np.absolute(edges))

print(edges[9][10], "side")
print(edges[10][10], " middle")
print(edges[11][11], " corner")
print(edges[8][10], "side -1")
print(edges[12][12], " corner +1")
# Display the original image and the edges
cv2.imshow('Original Image', image)
cv2.imshow('Sobel Edges', edges)
cv2.waitKey(0)
cv2.destroyAllWindows()
