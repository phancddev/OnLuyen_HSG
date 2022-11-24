Program khai_trien;
uses crt;
var m:array[1..100] of integer;
n,i,j,bac:integer;
 Begin
write('Nhap bac n: ');readln(n);
Clrscr;
for i:=1 to n+1 do m[i]:=0; m[1]:=1;

for i:=0 to n do
 Begin
for j:=i+1 downto 2 do m[j]:=m[j]+m[j-1];
writeln;
 end;
writeln;
bac:=n;
writeln('Khai trien nhi thu bac n: ');
writeln(bac);
for i:=2 to n do
 Begin
bac:=bac-1;
writeln(m[i]);
writeln(bac);
writeln(n-bac);
 end;
writeln(n);
readln
 end.
