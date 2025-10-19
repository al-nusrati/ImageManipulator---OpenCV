# Image Manipulation using OpenCV - Assignment 2

## 📋 Overview

This project implements an image manipulation system using OpenCV and C++. It demonstrates fundamental image processing operations including contrast enhancement, rotation, and flipping using Object-Oriented Programming principles.

## 🎯 Features

- ✅ Load and display images
- ✅ Manual contrast enhancement (without `convertTo()`)
- ✅ Adjustable brightness control
- ✅ Image rotation (90°, 180°, 270°)
- ✅ Image flipping (horizontal, vertical, both)
- ✅ Interactive menu-driven interface
- ✅ Save processed images
- ✅ Object-oriented design with proper encapsulation

## 📁 Project Structure

```
ImageManipulator/
├── ImageManipulator.h       # Header file with class declaration
├── ImageManipulator.cpp     # Implementation file
├── main.cpp                 # Main program with interactive menu
├── demo.cpp                 # Automated demonstration (optional)
├── CMakeLists.txt          # CMake build configuration
└── README.md               # This file
```

## 🔧 Prerequisites

### Required Software:
1. **C++ Compiler**
   - GCC 7.0+ (Linux/Mac)
   - Visual Studio 2017+ (Windows)
   - Clang 5.0+

2. **OpenCV Library** (Version 3.x or 4.x)
   - Install on Ubuntu/Debian:
     ```bash
     sudo apt-get update
     sudo apt-get install libopencv-dev
     ```
   - Install on macOS:
     ```bash
     brew install opencv
     ```
   - Install on Windows: Download from [OpenCV.org](https://opencv.org/releases/)

3. **CMake** (Optional, version 3.10+)
   ```bash
   sudo apt-get install cmake  # Ubuntu/Debian
   brew install cmake          # macOS
   ```

## 🚀 Building the Project

### Method 1: Using CMake (Recommended)

```bash
# Create build directory
mkdir build
cd build

# Generate build files
cmake ..

# Compile
make

# Run the program
./ImageManipulator
```

### Method 2: Manual Compilation

**Linux/Mac:**
```bash
g++ -o ImageManipulator main.cpp ImageManipulator.cpp `pkg-config --cflags --libs opencv4`
./ImageManipulator
```

**Windows (with OpenCV installed):**
```bash
g++ -o ImageManipulator.exe main.cpp ImageManipulator.cpp -I"C:\opencv\include" -L"C:\opencv\lib" -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc
ImageManipulator.exe
```

### Method 3: Using Visual Studio (Windows)

1. Create new C++ project
2. Add all `.cpp` and `.h` files
3. Configure OpenCV:
   - Project Properties → C/C++ → Additional Include Directories → Add OpenCV include path
   - Project Properties → Linker → Additional Library Directories → Add OpenCV lib path
   - Project Properties → Linker → Input → Add required .lib files
4. Build and run

## 📖 Usage Guide

### Running the Main Program

1. Start the program:
   ```bash
   ./ImageManipulator
   ```

2. Enter image path when prompted:
   ```
   Enter image path: /path/to/your/image.jpg
   ```

3. Choose operations from menu:
   ```
   ========== Image Manipulator Menu ==========
   1. Display Original Image
   2. Enhance Contrast
   3. Rotate Image (90°)
   4. Rotate Image (180°)
   5. Rotate Image (270°)
   6. Flip Horizontally
   7. Flip Vertically
   8. Flip Both Directions
   9. Save Processed Image
   10. Load New Image
   0. Exit
   ```

### Example Operations

#### Contrast Enhancement:
```
Choose option 2
Enter alpha: 1.5    (increases contrast)
Enter beta: 20      (increases brightness)
```

**Alpha Guidelines:**
- `alpha > 1.0`: Increases contrast (e.g., 1.5, 2.0)
- `alpha = 1.0`: No contrast change
- `alpha < 1.0`: Decreases contrast (e.g., 0.5, 0.7)

**Beta Guidelines:**
- `beta > 0`: Increases brightness (e.g., 20, 50)
- `beta = 0`: No brightness change
- `beta < 0`: Decreases brightness (e.g., -20, -50)

#### Rotation:
```
Choose option 3, 4, or 5
- Option 3: Rotates 90° clockwise
- Option 4: Rotates 180°
- Option 5: Rotates 270° (90° counter-clockwise)
```

#### Flipping:
```
Choose option 6, 7, or 8
- Option 6: Horizontal flip (mirror left-right)
- Option 7: Vertical flip (mirror top-bottom)
- Option 8: Both directions (equivalent to 180° rotation)
```

### Running the Demo Program (Optional)

Compile and run the automated demo:
```bash
g++ -o demo demo.cpp ImageManipulator.cpp `pkg-config --cflags --libs opencv4`
./demo
```

This will automatically demonstrate all operations with preset values.

## 🔍 Implementation Details

### Class Design

The `ImageManipulator` class follows OOP principles:

**Encapsulation:**
- Private data members (`originalImage`, `processedImage`, `imagePath`)
- Public interface methods for all operations

**Key Methods:**

1. **`loadImage(path)`** - Loads image from file
2. **`enhanceContrast(alpha, beta)`** - Manual pixel-by-pixel contrast adjustment
3. **`rotateImage(angle)`** - Rotates image by 90°, 180°, or 270°
4. **`flipImage(flipCode)`** - Flips image horizontally, vertically, or both
5. **`displayOriginal()`** - Shows original image
6. **`displayProcessed()`** - Shows processed image
7. **`saveImage(path)`** - Saves processed image to file

### Contrast Enhancement Algorithm

**Important:** We do NOT use `convertTo()` as required by the assignment.

**Manual Implementation:**
```cpp
for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
        for (each channel in pixel) {
            new_value = alpha * old_value + beta
            new_value = clamp(new_value, 0, 255)
            output_pixel[channel] = new_value
        }
    }
}
```

**Why Manual Implementation?**
- Demonstrates understanding of image structure
- Shows pixel-level manipulation skills
- Allows custom processing logic
- Educational value in learning low-level operations

## 📊 Sample Results

### Contrast Enhancement Examples:

| Parameters | Effect |
|------------|--------|
| alpha=1.5, beta=0 | Increased contrast, same brightness |
| alpha=1.0, beta=50 | Same contrast, increased brightness |
| alpha=1.3, beta=20 | Both increased |
| alpha=0.7, beta=-30 | Both decreased (darker, less contrast) |

### Geometric Transformations:

| Operation | Result |
|-----------|--------|
| Rotate 90° | Portrait ↔ Landscape conversion |
| Rotate 180° | Upside down |
| Flip Horizontal | Mirror image (left becomes right) |
| Flip Vertical | Upside down mirror |

## 🐛 Troubleshooting

### Issue: "Could not load image"
**Solution:** 
- Check if file path is correct
- Ensure image format is supported (JPG, PNG, BMP, etc.)
- Use absolute path if relative path fails

### Issue: "OpenCV not found"
**Solution:**
```bash
# Verify OpenCV installation
pkg-config --modversion opencv4

# If not found, reinstall OpenCV
sudo apt-get install libopencv-dev
```

### Issue: Compilation errors
**Solution:**
- Ensure C++11 or later standard
- Check OpenCV include paths
- Verify all library links

### Issue: Images not displaying
**Solution:**
- Check if display server is running (Linux)
- Ensure GUI support in OpenCV build
- Try saving image instead of displaying

## 📝 Assignment Checklist

- [x] Image loading and display
- [x] Contrast enhancement with user input (alpha/beta)
- [x] Manual implementation (NO `convertTo()`)
- [x] Rotation by 90°, 180°, 270°
- [x] Flipping (horizontal, vertical, both)
- [x] Object-oriented implementation
- [x] Class diagram
- [x] Documentation and report
- [x] Screenshots of results
- [x] Explanation of operations

## 🎓 Learning Outcomes

After completing this assignment, you will understand:

1. **Image Representation**
   - Images as 2D/3D matrices
   - Pixel value ranges (0-255)
   - Color channels (BGR in OpenCV)

2. **Linear Transformations**
   - Contrast adjustment using multiplication
   - Brightness adjustment using addition
   - Clamping values to valid range

3. **Geometric Transformations**
   - Rotation mechanics
   - Flipping operations
   - Coordinate transformations

4. **OOP in C++**
   - Class design and encapsulation
   - Constructor/destructor usage
   - Method organization

5. **OpenCV Basics**
   - cv::Mat class
   - Image I/O operations
   - Basic image processing functions

## 📚 Additional Resources

- [OpenCV Documentation](https://docs.opencv.org/)
- [OpenCV Tutorials](https://docs.opencv.org/master/d9/df8/tutorial_root.html)
- [Image Processing Fundamentals](https://en.wikipedia.org/wiki/Digital_image_processing)
- [Linear Transformation in Images](https://docs.opencv.org/master/d3/dc1/tutorial_basic_linear_transform.html)

## 🤝 Contributing

This is an academic assignment. If you want to extend it:
- Add more image filters (blur, sharpen, edge detection)
- Implement custom rotation angles
- Add histogram equalization
- Support batch processing

## 📄 License

This project is for educational purposes as part of an academic assignment.

## ✍️ Author

**Jawad Ahmed**  
**Roll Number:** 533047 
**Course:** Object Oriented Programming 
**Assignment:** Assignment 2 - Image Manipulation using OpenCV

---

## 🎯 Quick Start Summary

```bash
# 1. Install OpenCV
sudo apt-get install libopencv-dev

# 2. Clone/Download project files

# 3. Build
mkdir build && cd build
cmake ..
make

# 4. Run
./ImageManipulator

# 5. Enter image path and enjoy!
```

---

**Last Updated:** October 2025
