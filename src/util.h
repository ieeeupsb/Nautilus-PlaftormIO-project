
enum Color{
    BLUE,
    GREEN,
    RED
};

struct Box
{
    int num;
    int pos;
    Color color;
};

struct Port {
    unsigned int pos;
    boolean occupied;
};

class boxComparision {
    public:
        bool operator() (const Box& lhs, const Box& rhs) const {
            return lhs.color < rhs.color;
        }
};

Color changeToColor(char c) {
    switch (c)
    {
    case 'w':
        return RED;
    case 'u':
        return GREEN;
    case 'o':
        return BLUE;
    default:
        break;
    }
}

// Unsafe function
// second argument must have size 4
// bool initialize_boxes(long int msg,Box *arr) {
//     if((char)(msg >> 40) != 'W' || (char)(msg >> 32) != 'U')
//         return false;
//     arr[0].color = changeToColor((char)(msg >> 24));
//     arr[0].num = 0;
//     arr[1].color = changeToColor((char)(msg >> 16));
//     arr[1].num = 1;
//     arr[2].color = changeToColor((char)(msg >> 8));
//     arr[2].num = 2;
//     arr[3].color = changeToColor((char)(msg));
//     arr[3].num = 3;
//     return true;
// }
