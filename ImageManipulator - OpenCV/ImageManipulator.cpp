#include "ImageManipulator.h"

// Default Constructor
ImageManipulator::ImageManipulator() : imagePath("") {
    cout << "ImageManipulator object created." << endl;
}

// Parameterized Constructor
ImageManipulator::ImageManipulator(const string& path) : imagePath(path) {
    cout << "ImageManipulator object created." << endl;
    loadImage(path);
}

// Destructor
ImageManipulator::~ImageManipulator() {
    originalImage.release();
    processedImage.release();
    cout << "ImageManipulator object destroyed." << endl;
}

// Load Image
bool ImageManipulator::loadImage(const string& path) {
    originalImage = imread(path);

    if (originalImage.empty()) {
        cerr << "Error: Could not load image from " << path << endl;
        return false;
    }

    imagePath = path;
    cout << "Image loaded successfully!" << endl;
    cout << "Image size: " << originalImage.cols << "x" << originalImage.rows << endl;
    cout << "Channels: " << originalImage.channels() << endl;
    return true;
}

// Display Original Image (FIXED WINDOW SIZE)
void ImageManipulator::displayOriginal() const {
    if (originalImage.empty()) {
        cerr << "Error: No image loaded!" << endl;
        return;
    }

    namedWindow("Original Image", WINDOW_NORMAL);
    resizeWindow("Original Image", 800, 600);
    imshow("Original Image", originalImage);
    waitKey(0);
}

// Display Processed Image (FIXED WINDOW SIZE)
void ImageManipulator::displayProcessed(const string& windowName) const {
    if (processedImage.empty()) {
        cerr << "Error: No processed image available!" << endl;
        return;
    }

    namedWindow(windowName, WINDOW_NORMAL);
    resizeWindow(windowName, 800, 600);
    imshow(windowName, processedImage);
    waitKey(0);
}

// Enhance Contrast - MANUAL IMPLEMENTATION (NO convertTo)
Mat ImageManipulator::enhanceContrast(double alpha, double beta) {
    if (originalImage.empty()) {
        cerr << "Error: No image loaded!" << endl;
        return Mat();
    }

    // Create output image with same size and type
    processedImage = Mat::zeros(originalImage.size(), originalImage.type());

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
                Vec3b pixel = originalImage.at<Vec3b>(row, col);
                Vec3b newPixel;

                // Process each channel (B, G, R)
                for (int c = 0; c < 3; c++) {
                    double newValue = alpha * pixel[c] + beta;

                    // Clamp values to valid range [0, 255]
                    if (newValue > 255.0) newValue = 255.0;
                    if (newValue < 0.0) newValue = 0.0;

                    newPixel[c] = static_cast<uchar>(newValue);
                }

                processedImage.at<Vec3b>(row, col) = newPixel;
            }
        }
    }

    cout << "Contrast enhanced with alpha=" << alpha << ", beta=" << beta << endl;
    return processedImage;
}

// Rotate Image
Mat ImageManipulator::rotateImage(int angle) {
    if (originalImage.empty()) {
        cerr << "Error: No image loaded!" << endl;
        return Mat();
    }

    RotateFlags rotateCode;

    switch (angle) {
    case 90:
        rotateCode = ROTATE_90_CLOCKWISE;
        break;
    case 180:
        rotateCode = ROTATE_180;
        break;
    case 270:
        rotateCode = ROTATE_90_COUNTERCLOCKWISE;
        break;
    default:
        cerr << "Error: Invalid angle. Use 90, 180, or 270." << endl;
        return Mat();
    }

    rotate(originalImage, processedImage, rotateCode);
    cout << "Image rotated by " << angle << " degrees" << endl;
    return processedImage;
}

// Flip Image
Mat ImageManipulator::flipImage(int flipCode) {
    if (originalImage.empty()) {
        cerr << "Error: No image loaded!" << endl;
        return Mat();
    }

    // flipCode: 0 = vertical, 1 = horizontal, -1 = both
    flip(originalImage, processedImage, flipCode);

    string flipType;
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

    cout << "Image flipped " << flipType << endl;
    return processedImage;
}

// Get Original Image
Mat ImageManipulator::getOriginalImage() const {
    return originalImage;
}

// Get Processed Image
Mat ImageManipulator::getProcessedImage() const {
    return processedImage;
}

// Check if image is loaded
bool ImageManipulator::isImageLoaded() const {
    return !originalImage.empty();
}

// Save Processed Image
bool ImageManipulator::saveImage(const string& outputPath) const {
    if (processedImage.empty()) {
        cerr << "Error: No processed image to save!" << endl;
        return false;
    }

    bool success = imwrite(outputPath, processedImage);
    if (success) {
        cout << "Image saved to " << outputPath << endl;
    }
    else {
        cerr << "Error: Could not save image!" << endl;
    }
    return success;
}