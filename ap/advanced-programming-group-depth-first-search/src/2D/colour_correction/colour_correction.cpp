// Group Name: Depth First Search
// Group Members:
// - Alex Njeumi(Acse-ann23)
// - Yixiao Jing(acse-yj823)
// - Andrei Danila(edsml-acd23)
// - Fan Huang(acse-fh223)
// - Shrreya Behll(edsml-sb3323)
// - Wenxin Zhang(acse-wz2723)
#include <iostream>
#include <cmath>
#include <cstdlib> // For malloc and exit
#include <vector>
#include <algorithm>

#include <limits.h>
#include "colour_correction.h"
#include <random>

/**
 * @brief Function to apply grayscale to an image. It calculates the grayscale value for each pixel and assigns it to all three channels for RGB compatibility.
 * @param img - Reference to the image object.
 */
void applyGrayscale(Image& img) {
    int width = img.getWidth();
    int height = img.getHeight();
    auto data = img.getData(); // Assume this returns a copy or a const reference

    // Create a new data structure for the modified image
    std::vector<std::vector<std::vector<unsigned char> > > newGrayData(
            height, std::vector<std::vector<unsigned char> >(width, std::vector<unsigned char>(3))); // Keeping 3 channels for compatibility

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Compute the grayscale value
            const unsigned char& r = data[y][x][0];
            const unsigned char& g = data[y][x][1];
            const unsigned char& b = data[y][x][2];
            unsigned char gray = static_cast<unsigned char>(0.2126 * r + 0.7152 * g + 0.0722 * b);

            // Assign the grayscale value to all three channels for RGB compatibility
            newGrayData[y][x][0] = gray;
            newGrayData[y][x][1] = gray;
            newGrayData[y][x][2] = gray;
        }
    }

    // Update the image with the new data
    img.setData(newGrayData);
}


/**
 * @brief Function to clamp the color value to the range [0, 255].
 * @param value - The color value to be clamped.
 * @return - The clamped color value.
 */
unsigned char ClampColorValue(int value) {
    if (value < 0) return 0;
    if (value > 255) return 255;
    return static_cast<unsigned char>(value);
}

/**
 * Function to apply the brightness dullness filter to the input image.
 * @param img - Reference to the image object.
 * @param brightnessAdjustment - The brightness adjustment value. Default is INT_MIN.
 */
void applyBrightnessDullness(Image& img, int brightnessAdjustment = INT_MIN) {
    auto data = img.getData();
    int width = img.getWidth();
    int height = img.getHeight();
    int channels = img.getChannels();

    if (brightnessAdjustment == INT_MIN) {
        long long totalBrightness = 0;
        for (const auto& row : data) {
            for (const auto& pixel : row) {
                for (int ch = 0; ch < channels; ++ch) {
                    totalBrightness += pixel[ch];
                }
            }
        }
        long long averageBrightness = totalBrightness / (width * height * channels);
        brightnessAdjustment = 128 - static_cast<int>(averageBrightness);
    }

    for (auto& row : data) {
        for (auto& pixel : row) {
            for (int ch = 0; ch < channels; ++ch) {
                pixel[ch] = ClampColorValue(pixel[ch] + brightnessAdjustment);
            }
        }
    }

    img.setData(data);
}

/**
 * @brief Function to convert the input image to grayscale and apply histogram equalization.
 * @param img - Reference to the image object.
 */

void applyGrayscaleEqualization(Image& img) {
    // Convert to grayscale first
    applyGrayscale(img);

    // Assuming the grayscale image data has been set
    auto data = img.getData();
    int width = img.getWidth();
    int height = img.getHeight();

    std::vector<int> histogram(256, 0);
    for (const auto& row : data) {
        for (const auto& pixel : row) {
            histogram[pixel[0]]++;
        }
    }

    std::vector<float> cdf(256, 0.0f);
    cdf[0] = histogram[0];
    for (size_t i = 1; i < histogram.size(); ++i) {
        cdf[i] = cdf[i - 1] + histogram[i];
    }

    float cdfMin = *std::min_element(cdf.begin(), cdf.end());
    float cdfRange = cdf[255] - cdfMin;
    for (auto& row : data) {
        for (auto& pixel : row) {
            pixel[0] = static_cast<unsigned char>((cdf[pixel[0]] - cdfMin) / cdfRange * 255.0f);
        }
    }

    img.setData(data);
}


/**
 * @brief Function to convert RGB to HSV.
 * @param r - Red channel value.
 * @param g - Green channel value.
 * @param b - Blue channel value.
 * @return - The HSV pixel.
 */
HSVPixel RGBToHSV(unsigned char r, unsigned char g, unsigned char b) {
    float rf = r / 255.0f;
    float gf = g / 255.0f;
    float bf = b / 255.0f;

    float max = std::max({rf, gf, bf}), min = std::min({rf, gf, bf});
    float h, s, v = max;

    float d = max - min;
    s = max == 0 ? 0 : d / max;

    if (max == min) {
        h = 0; // achromatic
    } else {
        if (max == rf) {
            h = (gf - bf) / d + (gf < bf ? 6 : 0);
        } else if (max == gf) {
            h = (bf - rf) / d + 2;
        } else if (max == bf) {
            h = (rf - gf) / d + 4;
        }
        h /= 6;
    }

    return {h, s, v};
}

/**
 * @brief Function to convert HSV to RGB.
 * @param h - Hue value.
 * @param s - Saturation value.
 * @param v - Value.
 * @param r - Reference to the red channel value.
 * @param g - Reference to the green channel value.
 * @param b - Reference to the blue channel value.
 */
void HSVToRGB(float h, float s, float v, unsigned char &r, unsigned char &g, unsigned char &b) {
    int i = h * 6;
    float f = h * 6 - i;
    float p = v * (1 - s);
    float q = v * (1 - f * s);
    float t = v * (1 - (1 - f) * s);

    switch (i % 6) {
        case 0: r = v * 255, g = t * 255, b = p * 255; break;
        case 1: r = q * 255, g = v * 255, b = p * 255; break;
        case 2: r = p * 255, g = v * 255, b = t * 255; break;
        case 3: r = p * 255, g = q * 255, b = v * 255; break;
        case 4: r = t * 255, g = p * 255, b = v * 255; break;
        case 5: r = v * 255, g = p * 255, b = q * 255; break;
    }
}

/**
 * @brief Function to apply RGB to HSV equalization.
 * @param img - Reference to the image object.
 */
void applyRGB_HSVEqualization(Image& img) {
    auto data = img.getData();
    int width = img.getWidth();
    int height = img.getHeight();
    int channels = img.getChannels();

    if (channels < 3) {
        std::cerr << "Image must have at least 3 channels (RGB) for HSV equalization.\n";
        return; // Exiting the function as we cannot proceed with less than 3 channels
    }

    // Convert to HSV and calculate histogram for V channel
    std::vector<float> vValues(width * height);
    std::vector<int> histogram(256, 0);
    for (int i = 0; i < width * height; ++i) {
        int y = i / width;
        int x = i % width;
        HSVPixel hsv = RGBToHSV(data[y][x][0], data[y][x][1], data[y][x][2]);
        vValues[i] = hsv.v;

        int vIntensity = static_cast<int>(hsv.v * 255.0f);
        histogram[vIntensity]++;
    }

    // Calculate the Cumulative Distribution Function (CDF)
    std::vector<float> cdf(256, 0.0f);
    cdf[0] = histogram[0];
    for (int i = 1; i < 256; ++i) {
        cdf[i] = cdf[i - 1] + histogram[i];
    }

    float cdfMin = *std::min_element(cdf.begin(), cdf.end());
    float cdfMax = cdf[255];
    float cdfRange = cdfMax - cdfMin;

    // Apply the equalized V channel to all RGB channels
    for (int i = 0; i < width * height; ++i) {
        int y = i / width;
        int x = i % width;
        HSVPixel hsv = RGBToHSV(data[y][x][0], data[y][x][1], data[y][x][2]);
        hsv.v = (cdf[static_cast<int>(hsv.v * 255.0f)] - cdfMin) / cdfRange;

        unsigned char r, g, b;
        HSVToRGB(hsv.h, hsv.s, hsv.v, r, g, b);

        data[y][x][0] = r;
        data[y][x][1] = g;
        data[y][x][2] = b;
    }

    img.setData(data);
}


/**
 * @brief Function to convert RGB to HSL.
 * @param r - Red channel value.
 * @param g - Green channel value.
 * @param b - Blue channel value.
 * @return - The HSL pixel.
 */
HSLPixel RGBToHSL(unsigned char r, unsigned char g, unsigned char b) {
    float rf = r / 255.0f;
    float gf = g / 255.0f;
    float bf = b / 255.0f;

    float max = std::max({rf, gf, bf}), min = std::min({rf, gf, bf});
    float h, s, l = (max + min) / 2;

    float d = max - min;
    s = (l > 0.5f) ? d / (2 - max - min) : d / (max + min);

    if (max == min) {
        h = 0; // achromatic
    } else {
        if (max == rf) {
            h = (gf - bf) / d + (gf < bf ? 6 : 0);
        } else if (max == gf) {
            h = (bf - rf) / d + 2;
        } else if (max == bf) {
            h = (rf - gf) / d + 4;
        }
        h /= 6;
    }

    return {h, s, l};
}

/**
 * @brief Function to convert HSL to RGB.
 * @param h - Hue value.
 * @param s - Saturation value.
 * @param l - Lightness value.
 * @param r - Reference to the red channel value.
 * @param g - Reference to the green channel value.
 * @param b - Reference to the blue channel value.
 */
void HSLToRGB(float h, float s, float l, unsigned char &r, unsigned char &g, unsigned char &b) {
    auto hueToRGB = [](float p, float q, float t) {
        if (t < 0) t += 1;
        if (t > 1) t -= 1;
        if (t < 1.0f / 6) return p + (q - p) * 6 * t;
        if (t < 1.0f / 2) return q;
        if (t < 2.0f / 3) return p + (q - p) * (2.0f / 3 - t) * 6;
        return p;
    };

    float q = l < 0.5f ? l * (1 + s) : l + s - l * s;
    float p = 2 * l - q;
    float r_f = hueToRGB(p, q, h + 1.0f / 3);
    float g_f = hueToRGB(p, q, h);
    float b_f = hueToRGB(p, q, h - 1.0f / 3);

    r = static_cast<unsigned char>(r_f * 255);
    g = static_cast<unsigned char>(g_f * 255);
    b = static_cast<unsigned char>(b_f * 255);
}

/**
 * @brief Function to apply RGB to HSL equalization.
 * @param img - Reference to the image object.
 */
void applyRGB_HSLEqualization(Image& img) {
    auto data = img.getData();
    int width = img.getWidth();
    int height = img.getHeight();
    int channels = img.getChannels();

    if (channels < 3) {
        std::cerr << "Image must have at least 3 channels (RGB) for HSL equalization.\n";
        return; // Exiting the function as we cannot proceed with less than 3 channels
    }

    // Prepare data structure for equalized image data
    std::vector<std::vector<std::vector<unsigned char> > > newData(height, std::vector<std::vector<unsigned char> > (width, std::vector<unsigned char>(channels, 0)));

    // Convert to HSL and calculate histogram for L channel
    std::vector<float> lValues(width * height);
    std::vector<int> histogram(256, 0);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            HSLPixel hsl = RGBToHSL(data[y][x][0], data[y][x][1], data[y][x][2]);
            lValues[y * width + x] = hsl.l;
            int lIntensity = static_cast<int>(hsl.l * 255.0);
            histogram[lIntensity]++;
        }
    }

    // Calculate the Cumulative Distribution Function (CDF)
    std::vector<float> cdf(256, 0.0);
    cdf[0] = histogram[0];
    for (int i = 1; i < 256; ++i) {
        cdf[i] = cdf[i - 1] + histogram[i];
    }

    float cdfMin = *std::min_element(cdf.begin(), cdf.end());
    float cdfMax = cdf[255];
    float cdfRange = cdfMax - cdfMin;
    for (int i = 0; i < 256; ++i) {
        cdf[i] = (cdf[i] - cdfMin) / cdfRange * 255.0;
    }

    // Apply the equalized L channel to all RGB channels
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            HSLPixel hsl = RGBToHSL(data[y][x][0], data[y][x][1], data[y][x][2]);
            hsl.l = cdf[static_cast<int>(hsl.l * 255.0)] / 255.0;
            unsigned char r, g, b;
            HSLToRGB(hsl.h, hsl.s, hsl.l, r, g, b);
            newData[y][x][0] = r;
            newData[y][x][1] = g;
            newData[y][x][2] = b;
            if (channels == 4) { // Preserve alpha channel if present
                newData[y][x][3] = data[y][x][3];
            }
        }
    }

    // Update the image data
    img.setData(newData);
}

/**
 * @brief Function to find the minimum of three float values.
 * @param a - First float value.
 * @param b - Second float value.
 * @param c - Third float value.
 * @return - The minimum float value.
 */
float minOfThree(float a, float b, float c) {
    return (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c);
}

/**
 * @brief Function to find the maximum of three float values.
 * @param a - First float value.
 * @param b - Second float value.
 * @param c - Third float value.
 * @return - The maximum float value.
 */
float maxOfThree(float a, float b, float c) {
    return (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
}

/**
 * @brief Function to convert Threshold HSL to RGB.
 * @param h - Hue value.
 * @param s - Saturation value.
 * @param l - Lightness value.
 * @param r - Reference to the red channel value.
 * @param g - Reference to the green channel value.
 * @param b - Reference to the blue channel value.
 */void ThresholdHSLtoRGB(float h, float s, float l, int& r, int& g, int& b) {
    if (l > 2){
        l = l/255;
    }
    float c = (1.0 - std::abs(2.0 * l - 1)) * s;
    float x = c * (1.0 - std::abs(std::fmod(h / 60.0, 2.0) - 1.0));
    float m = l - c / 2.0;

    float r1, g1, b1;
    if (h >= 0 && h < 60) {
        r1 = c; g1 = x; b1 = 0;
    } else if (h >= 60 && h < 120) {
        r1 = x; g1 = c; b1 = 0;
    } else if (h >= 120 && h < 180) {
        r1 = 0; g1 = c; b1 = x;
    } else if (h >= 180 && h < 240) {
        r1 = 0; g1 = x; b1 = c;
    } else if (h >= 240 && h < 300) {
        r1 = x; g1 = 0; b1 = c;
    } else {
        r1 = c; g1 = 0; b1 = x;
    }

    r = (r1 + m) * 255;
    g = (g1 + m) * 255;
    b = (b1 + m) * 255;
}

/**
 * @brief Function to convert Threshold HSV to RGB.
 * @param h - Hue value.
 * @param s - Saturation value.
 * @param v - Value.
 * @param r - Reference to the red channel value.
 * @param g - Reference to the green channel value.
 * @param b - Reference to the blue channel value.
 */void ThresholdHSVtoRGB(float h, float s, float v, int& r, int& g, int& b) {
    if (v > 2){
        v = v/255;
    }
    float c = v * s;
    float x = c * (1 - std::abs(std::fmod(h / 60.0, 2) - 1));
    float m = v - c;

    float r1, g1, b1;
    if (h >= 0 && h < 60) {
        r1 = c; g1 = x; b1 = 0;
    } else if (h >= 60 && h < 120) {
        r1 = x; g1 = c; b1 = 0;
    } else if (h >= 120 && h < 180) {
        r1 = 0; g1 = c; b1 = x;
    } else if (h >= 180 && h < 240) {
        r1 = 0; g1 = x; b1 = c;
    } else if (h >= 240 && h < 300) {
        r1 = x; g1 = 0; b1 = c;
    } else {
        r1 = c; g1 = 0; b1 = x;
    }


    r = (r1 + m) * 255;
    g = (g1 + m) * 255;
    b = (b1 + m) * 255;
}

/**
 * @brief Function to convert Threshold RGB to HSL.
 * @param r - Red channel value.
 * @param g - Green channel value.
 * @param b - Blue channel value.
 * @param hue - Reference to the hue value.
 * @param sat - Reference to the saturation value.
 * @param light - Reference to the lightness value.
 */
void ThresholdRGBtoHSL(int r, int g, int b, float& hue, float& sat, float& light){
    float r_prime = r/255.0;
    float g_prime = g/255.0;
    float b_prime = b/255.0;
    float c_max = maxOfThree(r_prime,g_prime,b_prime);
    float c_min = minOfThree(r_prime,g_prime,b_prime);
    float delta = c_max - c_min;

    if (c_max == r_prime){
        hue = static_cast<int>( 60 * std::fmod((g_prime-b_prime)/delta, 6 ));
    } else if (c_max == g_prime){
        hue = static_cast<int>( 60 * (b_prime-r_prime)/delta + 2);
    } else if (c_max == b_prime){
        hue = static_cast<int>( 60 * (r_prime-g_prime)/delta + 4);
    } else {
        hue = static_cast<int>(0);
    }
    //saturation calculation
    if (delta == 0){
        sat = 0;
    } else{
        sat = delta / (1 - std::abs(c_max+c_min-1));
    }

    // lightness calculation
    light = (c_max+c_min)/2;

}

/**
 * @brief Function to convert Threshold RGB to HSV.
 * @param r - Red channel value.
 * @param g - Green channel value.
 * @param b - Blue channel value.
 * @param hue - Reference to the hue value.
 * @param sat - Reference to the saturation value.
 * @param value - Reference to the value.
 */
void ThresholdRGBtoHSV(int r, int g, int b, float& hue, float& sat, float& value) {
    float r_prime = r/255.0;
    float g_prime = g/255.0;
    float b_prime = b/255.0;
    float cmax = maxOfThree(r_prime,g_prime,b_prime);
    float cmin = minOfThree(r_prime,g_prime,b_prime);
    float delta = cmax - cmin;

    // Hue calculation
    if (delta == 0) {
        hue = 0; // Undefined, any value is acceptable
    } else if (cmax == r) {
        hue = 60 * fmod(((g - b) / delta), 6);
    } else if (cmax == g) {
        hue = 60 * (((b - r) / delta) + 2);
    } else if (cmax == b) {
        hue = 60 * (((r - g) / delta) + 4);
    }
    if (hue < 0) {
        hue += 360;
    }

    // Saturation calculation
    if (cmax == 0) {
        sat = 0;
    } else {
        sat = delta / cmax;
    }

    // Value calculation
    value = cmax;

}

/**
 * @brief Function to apply a threshold to an image.
 * @param img - Reference to the image object.
 * @param L_or_V_or_G - Character representing the type of thresholding to be applied.
 * @param threshold - The threshold value.
 */
void applyThreshold(Image& img, char L_or_V_or_G, float threshold){
    std::vector<std::vector<std::vector<unsigned char> > >  data = img.getData();
    int height = img.getHeight();
    int width = img.getWidth();
    float hue,sat,light,value;

    for (int h =  0 ; h < height; h++){
        for (int w = 0 ; w < width; w++){

            switch (L_or_V_or_G){
                case 'L':
                    ThresholdRGBtoHSL(data[h][w][0],data[h][w][1],data[h][w][2],hue,sat,light);

                    if (light > threshold/255){ // turn white

                        data[h][w][0] = static_cast<int>(255);
                        data[h][w][1] = static_cast<int>(255);
                        data[h][w][2] = static_cast<int>(255);
                    }
                    else { // turn black

                        data[h][w][0] = static_cast<int>(0);
                        data[h][w][1] = static_cast<int>(0);
                        data[h][w][2] = static_cast<int>(0);
                    }
                case 'V':
                    ThresholdRGBtoHSV(data[h][w][0],data[h][w][1],data[h][w][2],hue,sat,value);

                    if (value > threshold/255){ // turn white

                        data[h][w][0] = static_cast<int>(255);
                        data[h][w][1] = static_cast<int>(255);
                        data[h][w][2] = static_cast<int>(255);
                    }
                    else { // turn black

                        data[h][w][0] = static_cast<int>(0);
                        data[h][w][1] = static_cast<int>(0);
                        data[h][w][2] = static_cast<int>(0);
                    }
                case 'G':

                    if (data[h][w][0] > threshold){ // turn white

                        data[h][w][0] = static_cast<int>(255);
                        data[h][w][1] = static_cast<int>(255);
                        data[h][w][2] = static_cast<int>(255);
                    }
                    else { // turn black

                        data[h][w][0] = static_cast<int>(0);
                        data[h][w][1] = static_cast<int>(0);
                        data[h][w][2] = static_cast<int>(0);
                    }
            }

        }

    }
    img.setData(data);
}

/**
 * @brief Function to apply salt and pepper noise to an image.
 * @param img - Reference to the image object.
 * @param percentage - The percentage of pixels to be modified.
 */
void applySaltPepperNoise(Image& img, int percentage) {
    std::vector<std::vector<std::vector<unsigned char> > >  data = img.getData();
    int height = img.getHeight();
    int width = img.getWidth();
    int channels = img.getChannels();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disw(0, width - 1);
    std::uniform_int_distribution<> dish(0, height - 1);
    std::uniform_int_distribution<> disn(0, 1); // For deciding between salt (1) and pepper (0)
    int modified_pxl = percentage * width * height / 100;
    for (int i = 0; i < modified_pxl; ++i) {
        int x = disw(gen);
        int y = dish(gen);
        unsigned char color = disn(gen) * 255; // 0 for pepper, 255 for salt
        for (int c = 0; c < channels; ++c) {
            data[y][x][c] = color;
        }
    }
    img.setData(data);
}