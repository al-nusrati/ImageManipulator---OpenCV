#include "ImageManipulator.h"

// Default Constructor
ImageManipulator::ImageManipulator() : imagePath("") {
    std::cout << "ImageManipulator object created." << std::endl;
}

// Parameterized Constructor
ImageManipulator::ImageManipulator(const std::string& path) : imagePath(path) {
    std::cout << "ImageManipulator object created." << std::endl;
    loadImage(path);
}

// Destructor
ImageManipulator::~ImageManipulator() {
    originalImage.release();
    processedImage.release();
    std::cout << "ImageManipulator object destroyed." << std::endl;
}

// Load Image
bool ImageManipulator::loadImage(const std::string& path) {
    originalImage = cv::imread(path);

    if (originalImage.empty()) {
        std::cerr << "Error: Could not load image from " << path << std::endl;
        return false;
    }

    imagePath = path;
    std::cout << "Image loaded successfully!" << std::endl;
    std::cout << "Image size: " << originalImage.cols << "x" << originalImage.rows << std::endl;
    std::cout << "Channels: " << originalImage.channels() << std::endl;
    return true;
}

// Display Original Image
void ImageManipulator::displayOriginal() const {
    if (originalImage.empty()) {
        std::cerr << "Error: No image loaded!" << std::endl;
        return;
    }
    cv::namedWindow("Original Image", cv::WINDOW_NORMAL); // ADD THIS LINE
    cv::imshow("Original Image", originalImage);
    cv::waitKey(0);
}

// Display Processed Image
void ImageManipulator::displayProcessed(const std::string& windowName) const {
    if (processedImage.empty()) {
        std::cerr << "Error: No processed image available!" << std::endl;
        return;
    }
    cv::namedWindow(windowName, cv::WINDOW_NORMAL); // ADD THIS LINE
    cv::imshow(windowName, processedImage);
    cv::waitKey(0);
}

// Enhance Contrast - MANUAL IMPLEMENTATION (NO convertTo)
cv::Mat ImageManipulator::enhanceContrast(double alpha, double beta) {
    if (originalImage.empty()) {
        std::cerr << "Error: No image loaded!" << std::endl;
        return cv::Mat();
    }

    // Create output image with same size and type
    processedImage = cv::Mat::zeros(originalImage.size(), originalImage.type());

    // Manual pixel-by-pixel manipulation
    // Formula: new_pixel = alpha * old_pixel + beta

    for (int row = 0; row < originalImage.rows; row++) {
        for (int col = 0; col < originalImage.cols; col++) {

            if (originalImage.channels() == 1) {
                // Grayscale image (single channel)
                uchar pixelValue = originalImage.at<uchar>(row, col);
                double newValue = alpha * pixelValue + beta;

                // Clamp values to valid range [0, 255]
                if (newValue > 255.0) newValue = 255.0;
                if (newValue < 0.0) newValue = 0.0;

                processedImage.at<uchar>(row, col) = static_cast<uchar>(newValue);
            }
            else if (originalImage.channels() == 3) {
                // Color image (3 channels - BGR)
                cv::Vec3b pixel = originalImage.at<cv::Vec3b>(row, col);
                cv::Vec3b newPixel;

                // Process each channel (B, G, R)
                for (int c = 0; c < 3; c++) {
                    double newValue = alpha * pixel[c] + beta;

                    // Clamp values to valid range [0, 255]
                    if (newValue > 255.0) newValue = 255.0;
                    if (newValue < 0.0) newValue = 0.0;

                    newPixel[c] = static_cast<uchar>(newValue);
                }

                processedImage.at<cv::Vec3b>(row, col) = newPixel;
            }
        }
    }

    std::cout << "Contrast enhanced with alpha=" << alpha << ", beta=" << beta << std::endl;
    return processedImage;
}

// Rotate Image
cv::Mat ImageManipulator::rotateImage(int angle) {
    if (originalImage.empty()) {
        std::cerr << "Error: No image loaded!" << std::endl;
        return cv::Mat();
    }

    cv::RotateFlags rotateCode;

    switch (angle) {
    case 90:
        rotateCode = cv::ROTATE_90_CLOCKWISE;
        break;
    case 180:
        rotateCode = cv::ROTATE_180;
        break;
    case 270:
        rotateCode = cv::ROTATE_90_COUNTERCLOCKWISE;
        break;
    default:
        std::cerr << "Error: Invalid angle. Use 90, 180, or 270." << std::endl;
        return cv::Mat();
    }

    cv::rotate(originalImage, processedImage, rotateCode);
    std::cout << "Image rotated by " << angle << " degrees" << std::endl;
    return processedImage;
}

// Flip Image
cv::Mat ImageManipulator::flipImage(int flipCode) {
    if (originalImage.empty()) {
        std::cerr << "Error: No image loaded!" << std::endl;
        return cv::Mat();
    }

    // flipCode: 0 = vertical, 1 = horizontal, -1 = both
    cv::flip(originalImage, processedImage, flipCode);

    std::string flipType;
    switch (flipCode) {
    case 0:
        flipType = "vertically";
        break;
    case 1:
        flipType = "horizontally";
        break;
    case -1:
        flipType = "both directions";
        break;
    default:
        flipType = "unknown";
    }

    std::cout << "Image flipped " << flipType << std::endl;
    return processedImage;
}

// Get Original Image
cv::Mat ImageManipulator::getOriginalImage() const {
    return originalImage;
}

// Get Processed Image
cv::Mat ImageManipulator::getProcessedImage() const {
    return processedImage;
}

// Check if image is loaded
bool ImageManipulator::isImageLoaded() const {
    return !originalImage.empty();
}

// Save Processed Image
bool ImageManipulator::saveImage(const std::string& outputPath) const {
    if (processedImage.empty()) {
        std::cerr << "Error: No processed image to save!" << std::endl;
        return false;
    }

    bool success = cv::imwrite(outputPath, processedImage);
    if (success) {
        std::cout << "Image saved to " << outputPath << std::endl;
    }
    else {
        std::cerr << "Error: Could not save image!" << std::endl;
    }
    return success;
}