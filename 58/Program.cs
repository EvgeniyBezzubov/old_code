Random x = new Random();
int m = 2;
int n = 2;
int tri_d = 2;
int[,,] array = new int[m, n, tri_d];

string res = "";

foreach (int x1 in Enumerable.Range(0, m))
{
   
    foreach (int y in Enumerable.Range(0, n))
    {
        foreach (int z in Enumerable.Range(0, tri_d))
        {
       
      // Double r = Convert.ToDouble(x.Next(-100, 100)/10.0);
            array[x1,y,z]= x.Next(10, 99);
            //Console.WriteLine(array[x1,y,z]);
            res = Convert.ToString(array[x1,y,z]) + " " + "(" + Convert.ToString(x1) + " " + Convert.ToString(y)+ " " + Convert.ToString(z) + ")";
            Console.WriteLine(res);
          
        }
    }
}