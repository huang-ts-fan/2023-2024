import cv2


def apply_gaussian_blur(image, kernel_size=(5, 5), sigma_x=0, sigma_y=0):
    """
    Apply Gaussian blur to an image.

    Args:
        image (numpy.ndarray): Input image.
        kernel_size (tuple): Kernel size for Gaussian blur. Default is (5, 5).
        sigma_x (float): Standard deviation in X direction. Default is 0.
        sigma_y (float): Standard deviation in Y direction. Default is 0.

    Returns:
        numpy.ndarray: Blurred image.
    """
    blurred_image = cv2.GaussianBlur(image, kernel_size, sigma_x, sigma_y)
    return blurred_image


# Example usage:
image_path = '/advanced-programming-group-depth-first-search/tests/2D/test_images/spotted50.png'
image = cv2.imread(image_path)

# Apply Gaussian blur with default parameters
blurred_image = apply_gaussian_blur(image)


print(blurred_image[9][10], "side")
print(blurred_image[10][10], " middle")
print(blurred_image[11][11], " corner")
print(blurred_image[8][10], "side -1")
print(blurred_image[12][12], " corner +1")
# Display the original and blurred images
cv2.imshow('Original Image', image)
cv2.imshow('Blurred Image', blurred_image)
cv2.waitKey(0)
cv2.destroyAllWindows()
