typedef struct PIXEL PIXEL;
typedef struct NODE NODE;

struct PIXEL{
    float posX, posY;
    float colorRed, colorBlue,colorGreen;
};

struct NODE{
    int value;
    struct NODE* next;
};