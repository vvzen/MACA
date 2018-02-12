void setup()
{
  size(400, 400);
  background(255);
  smooth();
}

void draw()
{
  mycircle(width/2, height/2, width);
}

void mycircle(int x, int y, float rad)
{
  if (rad>10)
  {
    ellipse(x, y, rad, rad);
    mycircle(x, y, rad/2);
  }
}

