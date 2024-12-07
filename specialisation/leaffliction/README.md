# Leafliction

**Leafliction** is a computer vision project focused on the automated acquisition, processing, analysis, and interpretation of digital images. By extracting high-dimensional data from the real world, this project aims to provide meaningful, symbolic information in the form of decisions or insights, particularly for leaf image analysis.

Computer vision is the transformation of visual inputs into descriptions of the world, enabling intelligent systems to make informed decisions. In this context, **Leafliction** seeks to extract symbolic information from image data through models built upon geometry, physics, statistics, and learning theory.

## Project Setup

To set up and run **Leafliction**, follow these steps:

1. **Create a Conda environment:**
   ```bash
   conda create --name leafliction-env python=3.10.14
   conda activate leafliction-env
   ```
2. **Install dependencies using Poetry:**
    ```bash
    pip install poetry
    poetry install
    ```
## Usage

Once the environment is set up, you can run the various components of **Leafliction** as follows:

1. **Run Distribution Analysis:**
    ```bash
    python src/distribution.py images
    ```
2. **Run Image Augmentation:**
    ```bash
    python src/augmentation.py images/Apple_Black_rot/image\ \(10\).JPG
    ```
3. **Run Image Transformation:**
    ```bash
    python src/transformation.py images/Apple_Black_rot/image\ \(10\).JPG
    ```
4. **Train the Model:**
    ```bash
    python src/train.py
    ```
5. **Make Predictions:**
    ```bash
    python src/predict.py
    ```

## Contributors

- **[jreivilo](https://github.com/jreivilo)** - Project creator
- **[Np93](https://github.com/Np93)** - Contributor
