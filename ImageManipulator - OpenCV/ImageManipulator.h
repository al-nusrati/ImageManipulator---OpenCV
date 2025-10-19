#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>

using namespace cv;
using namespace std;

class ImageManipulator {
private:
    Mat originalImage;
    Mat processedImage;
    string imagePath;

public:
    // Constructors
    ImageManipulator();
    ImageManipulator(const string& path);

    // Destructor
    ~ImageManipulator();

    // Image Loading
    bool loadImage(const string& path);

    // Display methods
    void displayOriginal() const;
    void displayProcessed(const string& windowName = "Processed Image") const;

    // Contrast Enhancement (Manual implementation - NO convertTo)
    Mat enhanceContrast(double alpha, double beta);

    // Image Rotation
    Mat rotateImage(int angle);

    // Image Flipping
    Mat flipImage(int flipCode);

    // Utility methods
    Mat getOriginalImage() const;
    Mat getProcessedImage() const;
    bool isImageLoaded() const;

    // Save processed image
    bool saveImage(const string& outputPath) const;
};
