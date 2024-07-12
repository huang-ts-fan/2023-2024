import cv2


def apply_median_blur(image_path, output_path, kernel_size):
    # Read the image
    original_image = cv2.imread(image_path)

    # Apply median blur
    blurred_image = cv2.medianBlur(original_image, kernel_size)

    # Display both images
    cv2.imshow('Original Image', original_image)
    cv2.imshow('Blurred Image', blurred_image)
    cv2.waitKey(0)  # Wait indefinitely until a key is pressed
    cv2.destroyAllWindows()  # Close all OpenCV windows


# Example usage:
input_image_path = "/advanced-programming-group-depth-first-search/tests/2D/test_images/spotted50.png"
kernel_size = 5  # Adjust kernel size as needed
apply_median_blur(input_image_path, kernel_size)
