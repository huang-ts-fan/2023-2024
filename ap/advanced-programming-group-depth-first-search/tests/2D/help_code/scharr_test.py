import cv2

# Read the input image
image = cv2.imread('advanced-programming-group-depth-first-search/tests/2D/test_images/spotted50.png', cv2.IMREAD_GRAYSCALE)

# Apply Scharr edge detection along the x-axis
scharr_x = cv2.Scharr(image, cv2.CV_64F, 1, 0)

# Apply Scharr edge detection along the y-axis
scharr_y = cv2.Scharr(image, cv2.CV_64F, 0, 1)

# Combine the x and y gradient images
scharr_edges = cv2.magnitude(scharr_x, scharr_y)

# Convert edges to uint8 for display
scharr_edges = cv2.convertScaleAbs(scharr_edges)


diff = []
for i in range(8,12):
    for j in range(8,12):
        # if scharr_edges[i][j] >= 100:
            print(" Height " + str(i) + " width  " + str(j) + " value ", scharr_edges[i][j])
            diff.append(image[i][j] - scharr_edges[i][j])



# Display the original image and the Scharr edges
cv2.imshow('Original Image', image)
cv2.imshow('Scharr Edges', scharr_edges)
cv2.waitKey(0)
cv2.destroyAllWindows()
