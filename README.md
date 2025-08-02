# Smart Image Resizer: Content-Aware Seam Carving in C++

This project implements **Content-Aware Image Resizing** using the **Seam Carving algorithm**. Seam carving allows intelligent resizing of images by preserving visually important content and removing low-energy pixels.

---

## 📌 Problem Statement

Apply the seam carving content-aware image-resizing algorithm on a given image. The target height and width (in pixels) are input by the user.

### 🧠 What is Seam Carving?

Seam carving is a technique to resize images without distorting or cropping important regions. It removes one vertical or horizontal seam (a path of connected pixels) at a time based on their **energy values**.

- **Vertical Seam**: Top to bottom path with one pixel per row.
- **Horizontal Seam**: Left to right path with one pixel per column.
- **Energy Function**: Measures the importance of each pixel (e.g., gradient magnitude).
- **Goal**: Remove the least important seams iteratively until the desired size is reached.

---

## 🔁 Program Flow

1. **Image Loading**  
   - Load input image using OpenCV and extract RGB values into a 3D matrix.

2. **Energy Calculation**  
   - Compute energy for each pixel (e.g., using gradient of neighboring pixels).

3. **Seam Identification**  
   - Find the lowest energy vertical or horizontal seam using dynamic programming.

4. **Seam Removal**  
   - Remove the identified seam from the image.

5. **Repeat**  
   - Repeat the process until the image reaches the user-specified width and height.

6. **Output**  
   - Save the resized image using OpenCV.

---

## 🧰 Requirements

- **C++ Compiler** (G++ or similar)
- **OpenCV (C++ Version)**

---

## ⚙️ How to Install OpenCV for C++ (Ubuntu/Linux)

```bash
sudo apt update
sudo apt install libopencv-dev

## ⚙️ How to Run

Compile using : g++ Seamcarving.cpp -o seamcarving `pkg-config --cflags --libs opencv4`
Run : ./seamcarving <Path to your image>
And then enter desired dimensions width and height

