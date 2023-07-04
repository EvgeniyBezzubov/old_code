Console.WriteLine("Задача 54");
var num = new List<int>() {};

int[,] numbers = { { 1, 4, 7, 2 }, { 5, 9, 2, 3}, { 8, 4, 2, 4}};
int[] temp={};

foreach (int i in Enumerable.Range(0, 3))
{
    foreach (int i2 in Enumerable.Range(0, 4))
    {
        num.Add(numbers[i,i2]); 
    }
    num.Sort();
    num.Reverse();
    foreach (int i2 in Enumerable.Range(0, 4))
    {
        numbers[i,i2] = num[i2];
        
    }
    num.Clear();
}

foreach (int i in numbers)
{
    Console.WriteLine(i);
}
