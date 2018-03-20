struct Snake
{
    char head;
    char body;
    int x_pos, y_pos;
    int tail_len;
    int tail_x[100], tail_y[100];
    Direction dir;
    Snake(int, int, char, char, Direction);
    ~Snake();
    void set_dir(char);
    void update();
    bool did_die(int, int);
    bool did_get_fruit(int, int);
};

Snake::Snake(int x, int y, char head_c, char body_c, Direction d)
{
    x_pos = x;
    y_pos = y;
    dir = d;
    head = head_c;
    body = body_c;
}

Snake::~Snake()
{
    delete[] tail_x;
    delete[] tail_y;
}

void Snake::set_dir(char key)
{
    switch (key)
    {
        case 'w':
            if (dir != DOWN) dir = UP;
            break;
        case 'a':
            if (dir != RIGHT) dir = LEFT;
            break;
        case 's':
            if (dir != UP) dir = DOWN;
            break;
        case 'd':
            if (dir != LEFT) dir = RIGHT;
            break;
    }
}

void Snake::update()
{
    int prev_x = tail_x[0];
    int prev_y = tail_y[0];
    int prev_2x, prev_2y;
    tail_x[0] = x_pos;
    tail_y[0] = y_pos;

    for (int i = 1; i < tail_len; i++)
    {
        prev_2x = tail_x[i];
        prev_2y = tail_y[i];
        tail_x[i] = prev_x;
        tail_y[i] = prev_y;
        prev_x = prev_2x;
        prev_y = prev_2y;
    }

    switch (dir)
    {
        case UP:
            y_pos--;
            break;
        case LEFT:
            x_pos--;
            break;
        case DOWN:
            y_pos++;
            break;
        case RIGHT:
            x_pos++;
            break;
    }
}

bool Snake::did_die(int w, int h)
{
    if (x_pos > w - 2 || x_pos < 1 || y_pos > h - 2 || y_pos < 1)
    {
        return true;
    }
    for (int i = 0; i < tail_len; i++)
    {
        if (tail_x[i] == x_pos && tail_y[i] == y_pos)
        {
            return true;
        }
    }
    return false;
}

bool Snake::did_get_fruit(int x, int y)
{
    bool flag = false;
    if (x_pos == x && y_pos == y)
    {
        flag = true;
        tail_len++;
    }
    return flag;
}