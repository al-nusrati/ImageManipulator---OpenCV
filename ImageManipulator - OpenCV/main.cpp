#include "ImageManipulator.h"

void displayMenu() {
    cout << "\n========== Image Manipulator Menu ==========" << endl;
    cout << "1. Display Original Image" << endl;
    cout << "2. Enhance Contrast" << endl;
    cout << "3. Rotate Image (90° Clockwise)" << endl;
    cout << "4. Rotate Image (180°)" << endl;
    cout << "5. Rotate Image (270° Clockwise)" << endl;
    cout << "6. Flip Horizontally" << endl;
    cout << "7. Flip Vertically" << endl;
    cout << "8. Flip Both Directions" << endl;
    cout << "9. Load New Image" << endl;
    cout << "0. Exit" << endl;
    cout << "============================================" << endl;
    cout << "Enter your choice: ";
}

int main() {
    string imagePath;

    cout << "========================================" << endl;
    cout << "  Image Manipulation using OpenCV" << endl;
    cout << "  Assignment 2" << endl;
    cout << "========================================" << endl;
    cout << "\nEnter image path: ";
    getline(cin, imagePath);

    ImageManipulator manipulator(imagePath);

    if (!manipulator.isImageLoaded()) {
        cerr << "\nFailed to load image. Exiting..." << endl;
        return -1;
    }

    int choice;
    bool running = true;

    while (running) {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "\nDisplaying original image..." << endl;
            manipulator.displayOriginal();
            break;
        }

        case 2: {
            double alpha, beta;
            cout << "\n--- Contrast Enhancement ---" << endl;
            cout << "Alpha (contrast control, recommended 0.5-3.0): ";
            cin >> alpha;
            cout << "Beta (brightness control, recommended -100 to 100): ";
            cin >> beta;

            manipulator.enhanceContrast(alpha, beta);
            manipulator.displayProcessed("Contrast Enhanced Image");
            break;
        }

        case 3: {
            cout << "\nRotating image 90° clockwise..." << endl;
            manipulator.rotateImage(90);
            manipulator.displayProcessed("Rotated 90° Clockwise");
            break;
        }

        case 4: {
            cout << "\nRotating image 180°..." << endl;
            manipulator.rotateImage(180);
            manipulator.displayProcessed("Rotated 180°");
            break;
        }

        case 5: {
            cout << "\nRotating image 270° clockwise..." << endl;
            manipulator.rotateImage(270);
            manipulator.displayProcessed("Rotated 270° (90° Counter-Clockwise)");
            break;
        }

        case 6: {
            cout << "\nFlipping image horizontally..." << endl;
            manipulator.flipImage(1); // Horizontal flip
            manipulator.displayProcessed("Flipped Horizontally");
            break;
        }

        case 7: {
            cout << "\nFlipping image vertically..." << endl;
            manipulator.flipImage(0); // Vertical flip
            manipulator.displayProcessed("Flipped Vertically");
            break;
        }

        case 8: {
            cout << "\nFlipping image in both directions..." << endl;
            manipulator.flipImage(-1); // Both directions
            manipulator.displayProcessed("Flipped Both Directions");
            break;
        }

        case 9: {
            cin.ignore(); // Clear input buffer
            cout << "\nEnter new image path: ";
            getline(cin, imagePath);
            if (manipulator.loadImage(imagePath)) {
                cout << "New image loaded successfully!" << endl;
            }
            else {
                cout << "Failed to load new image. Continuing with current image." << endl;
            }
            break;
        }

        case 0: {
            cout << "\nExiting program. Thank you!" << endl;
            running = false;
            break;
        }

        default: {
            cout << "\nInvalid choice! Please try again." << endl;
            break;
        }
        }
    }

    destroyAllWindows();
    return 0;
}