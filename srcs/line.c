void	find_end_p(int step, double delta)
{
	int x;
	int y;

	if(delta > 1 && delta <= step)
	{
		y = step;
		x = y * delta;
		return(x);
	}	
	else if(delta <= 1 && delta <= step)
	{
		x = step;
		y = x * delta;
		return (y);
	}
}