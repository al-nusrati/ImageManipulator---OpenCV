#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <iostream>

class ImageManipulator {
private:
    cv::Mat originalImage;
    cv::Mat processedImage;
    std::string imagePath;

public:
    // Constructors
    ImageManipulator();
    ImageManipulator(const std::string& path);

    // Destructor
    ~ImageManipulator();

    // Image Loading
    bool loadImage(const std::string& path);

    // Display methods
    void displayOriginal() const;
    void displayProcessed(const std::string& windowName = "Processed Image") const;

    // Contrast Enhancement (Manual implementation - NO convertTo)
    cv::Mat enhanceContrast(double alpha, double beta);

    // Image Rotation
    cv::Mat rotateImage(int angle);

    // Image Flipping
    cv::Mat flipImage(int flipCode);

    // Utility methods
    cv::Mat getOriginalImage() const;
    cv::Mat getProcessedImage() const;
    bool isImageLoaded() const;

    // Save processed image
    bool saveImage(const std::string& outputPath) const;
};
