Program Thetich;
Var
   Fx:array[0..100,0..100] of word;
   Lay:array[1..100] of boolean;
   A,B:array[1..100] of byte;
   n, V : byte;
   i,j : word;

Procedure Nhap;
   var f : text;
   Begin
      Assign(f,'THETICH.IN');
      Reset(f);
      Readln(f,n,V);
      FillChar(A,SizeOf(A),0);
      B:=A;
      For i:=1 to n do
         Readln(f,A[i],B[i]);
      Close(f);
   End;

Function GetMax(v1,v2:Word):Word;
   Begin
      If v1>v2 then GetMax:=v1 else GetMax:=v2;
   End;

Procedure Xuly;
   Begin
      FillChar(Fx,SizeOf(Fx),0);
      For i:=1 to n do
         For j:=1 to V do
         Begin
             If j>=A[i] then Fx[i,j]:=GetMax(Fx[i-1,j-A[i]]+B[i],Fx[i-1,j])
                else Fx[i,j]:=Fx[i-1,j];
         End;
   End;

Procedure Xuat;
   Var Max,v0,n0,v1:Word;
   Begin
      Max:=0;
      V0:=0;
      n0:=0;
      For i:=1 to V do If Max<=Fx[n,i] then
      Begin
         Max:=Fx[n,i];
         v0:=i;
      End;
      v1:=v0;
      For i:=n downto 1 do If Fx[i,v0]<>Fx[i-1,v0] then
      Begin
         Inc(n0);
         Writeln('Vat thu ', i,' - The tich ',A[i],' - Gia tri ',B[i]);
         v0:=v0-A[i];
      End;
      Writeln('Chon ',n0,' vat - Tong the tich ',v1,' - Tong gia tri ',Max);
   End;

BEGIN
   Nhap;
   Xuly;
   Xuat;
   Readln;
END.