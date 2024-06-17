
#include <iostream>
#include <algorithm>
#include <map>
#include <string>

using namespace std;

class Color {
public:
    int red, green, blue;

    Color(int r, int g, int b) : red(r), green(g), blue(b) {}

    bool operator<(const Color& other) const {
        if (red != other.red) return red < other.red;
        if (green != other.green) return green < other.green;
        return blue < other.blue;
    }

    static Color Red() {
        return Color(255, 0, 0);
    }

    static Color Green() {
        return Color(0, 255, 0);
    }

    static Color Blue() {
        return Color(0, 0, 255);
    }

    static Color linearInterpolated(const Color& a, const Color& b, float t) {
        int red = static_cast<int>(a.red + (b.red - a.red) * t);
        int green = static_cast<int>(a.green + (b.green - a.green) * t);
        int blue = static_cast<int>(a.blue + (b.blue - a.blue) * t);
        return Color(red, green, blue);
    }

    void print() const {
        cout << "Color(" << red << ", " << green << ", " << blue << ")" << endl;
    }
};

bool responseCheck(string arr[], string target, int size) {
    for (int i = 0; i < size; i++) {
        if (target == arr[i]) {
            return true;
        }
    }
    return false;
}

void initializeMap(const Color& color)
{
    map<Color, string> colorMap; 

    colorMap[Color::Red()] = "Red";
    colorMap[Color::Green()] = "Green";
    colorMap[Color::Blue()] = "Blue";
    colorMap[Color(255, 255, 0)] = "Yellow";
    colorMap[Color(0, 255, 255)] = "Cyan";
    colorMap[Color(255, 0, 255)] = "Magenta";
    colorMap[Color(192, 192, 192)] = "Silver";
    colorMap[Color(128, 128, 128)] = "Gray";
    colorMap[Color(128, 0, 0)] = "Maroon";
    colorMap[Color(128, 128, 0)] = "Olive";
    colorMap[Color(0, 128, 0)] = "Dark Green";
    colorMap[Color(128, 0, 128)] = "Purple";
    colorMap[Color(0, 128, 128)] = "Teal";
    colorMap[Color(0, 0, 128)] = "Navy";

    auto it = colorMap.find(color);
    if (it != colorMap.end())
    {
        cout << "The interpolated color (RGB): " << color.red << ", " << color.green << ", " << color.blue << endl;
        cout << "The corresponding name from the map is: " << it->second << endl;
    }
    else
    {
        cout << "Color not found in the map." << endl;
    }
}

Color getColorFrame(const string &colorName)
{
    if (colorName == "red") return Color::Red();
    if (colorName == "blue") return Color::Blue();
    if (colorName == "green") return Color::Green();

    return Color(0, 0, 0);
}

void lowerCase(string &str)
{
    transform(str.begin(), str.end(), str.begin(), ::tolower);
}

int main()
{
    string color1, color2; 
    string colorSets[] = {"red", "green", "blue"};
    int size_of_colorSets = sizeof(colorSets) / sizeof(colorSets[0]);

    do 
    {
        cout << "Please choose the first color (red, green, blue): ";
        getline(cin, color1);

        cout << "Please choose the second color (red, green, blue): ";
        getline(cin, color2);

        lowerCase(color1);
        lowerCase(color2);
    } while ((!responseCheck(colorSets, color1, size_of_colorSets)) || (!responseCheck(colorSets, color2, size_of_colorSets)));

    cout << "Your input is valid." << endl; 

    float t; 
    do
    {
        cout << "How much do you want to blend between these two selected colors? (range from 0-1) ";
        cin >> t;
    } while(t < 0.0f || t > 1.0f);

    Color c1 = getColorFrame(color1);
    Color c2 = getColorFrame(color2);

    Color LerpRGB = Color::linearInterpolated(c1, c2, t);
    initializeMap(LerpRGB);
    
    LerpRGB.print();

    return 0; 
}
