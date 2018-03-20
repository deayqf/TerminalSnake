struct Level
{
    int width, height;
    int fruit_x, fruit_y;
    char fruit;
    char wall;
    char map[22][22];
    char map_buff[22][22];
    Level(int, int, char, int, int, char);
    ~Level();
    void draw();
    void set_tile(int x, int y, Tile t, char tile = ' ')
    {
        switch (t)
        {
            case WALL:
                tile = wall;
                break;
            case FRUIT:
                tile = fruit;
        }
        map[y][x] = tile;
    }
};

Level::Level(int map_w, int map_h, char wall_c, int f_x, int f_y, char fruit_c) : 
    width(map_w), 
    height(map_h), 
    wall(wall_c),
    fruit_x(f_x),
    fruit_y(f_y), 
    fruit(fruit_c)
{}

Level::~Level()
{
    for (int i = 0; i < height; i++)
    {
        delete[] map[i];
        delete[] map_buff[i];
    }
    delete[] map;
    delete[] map_buff;
}

void Level::draw()
{
    int run = -1;
    memset((char*)map_buff, 0, width * height);
    for (int y = 0; y < height; y++)
    {
        run = -1;
        for (int x = 0; x < width; x++)
        {
            if (map[y][x] == map_buff[y][x])
            {
                if (run != -1)
                {
                    setCursorPosition(run, y);
                    cout.write(&map[y][run], x - run);
                    run = -1;
                }
            }
            else if (run == -1)
            {
                run = x;
            }
        }
        if (run != -1)
        {
            setCursorPosition(run, y);
            cout.write(&map[y][run], height - run);
        }
        cout << endl;
    }
    cout.flush();
    memcpy((char*)map_buff, (char const*)map, width * height);
}
