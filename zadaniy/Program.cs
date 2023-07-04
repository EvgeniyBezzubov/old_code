int Accerman_Levi(int M, int N,int sum = 0)
{
    
    if (M>0 & N>0)
    {
        return Accerman_Levi(M-1,Accerman_Levi(M,N-1));
    }
    else if (M>0 & N==0)
    {
        return Accerman_Levi(M-1,1);
    }
    else if (M==0)
    {
        
        return N+1;
    }
    else
    {
        return 1;
    }
    
}
Console.WriteLine(Accerman_Levi(3,2));
Console.WriteLine(Accerman_Levi(2,3));


