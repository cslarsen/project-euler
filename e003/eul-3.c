int main()
{
	__int64 number = 317584931803;
	int divisor = 2;
	while (number > 1) {
		if (0 == (number % divisor)) {
			number /= divisor;
			divisor--;
		}
		divisor++;
	}
	printf("%d\n", divisor);
}
