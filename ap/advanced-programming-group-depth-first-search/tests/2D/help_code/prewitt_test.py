import cv2
import numpy as np

# Read the input image
image = cv2.imread('advanced-programming-group-depth-first-search/tests/2D/test_images/spotted500.png', cv2.IMREAD_GRAYSCALE)

# Apply Prewitt edge detection along the x-axis
prewitt_x = cv2.filter2D(image, -1, np.array([[-1, 0, 1], [-1, 0, 1], [-1, 0, 1]]))

# Apply Prewitt edge detection along the y-axis
prewitt_y = cv2.filter2D(image, -1, np.array([[-1, -1, -1], [0, 0, 0], [1, 1, 1]]))


print(prewitt_x.shape)
print(prewitt_y.shape)
print(prewitt_x.dtype)
print(prewitt_y.dtype)
prewitt_x = prewitt_x.astype(np.float32)
prewitt_y = prewitt_y.astype(np.float32)
# Combine the x and y gradient images
prewitt_edges = cv2.magnitude(prewitt_x, prewitt_y)

# Convert edges to uint8 for display
prewitt_edges = np.uint8(prewitt_edges)

# print(prewitt_edges[4][5], "side")
# print(prewitt_edges[5][5], " middle")
# print(prewitt_edges[6][6], " corner")
# print(prewitt_edges[3][5], "side -1")
# print(prewitt_edges[7][7], " corner +1")

# for i in range(99,401):
#     print(" Height " + str(i) + " width 400 " + "value ", prewitt_edges[i][400])
#     print(" Height " + str(i) + " width 401 " + "value ", prewitt_edges[i][401])

# print(prewitt_edges[0][0])
diff = []
for i in range(9,12):
    for j in range(9,12):
        # if prewitt_edges[i][j] >= 100:
            print(" Height " + str(i) + " width  " + str(j) + " value ", prewitt_edges[i][j])
            diff.append(image[i][j] - prewitt_edges[i][j])


print(np.max(diff), diff.count(np.max(diff)))

            # print(image[i][j]  - prewitt_edges[i][j]) 
# Display the original image and the Prewitt edges
cv2.imshow('Original Image', image)
cv2.imshow('Prewitt Edges', prewitt_edges)
cv2.waitKey(0)
cv2.destroyAllWindows()
