`timescale 1ns / 1ps

module testing();
parameter word=16;
parameter fraction=14;
parameter exponent=word-fraction-1;
parameter int_upper=(2*fraction)+exponent; //upper limit of # int bits
reg [word-1:0] I [0:167];
reg [word-1:0] Q[0:167];
integer file,i;

 initial  begin 
 $readmemb("I_grid.txt",I );
$readmemb("Q_grid.txt",Q );
file=$fopen ("out.txt","w");
  for (i=0;i<167;i=i+1) begin
 $fwrite (file,"%0b",i);
 end  
$fclose (file);
  //#10   
 // $finish;
end
task Qmul;  //to convert 32 single point into fixed point
  input [word-1:0] a,b;
  output [word-1:0] out; //extra bit for sign
  reg [15:0] aa,bb;
  reg [(2*word)-1:0] temp;
  begin
     // N=(2*fraction)+exponent; //upper limit of # int bits
		if ((a[15]==1) && (b[15]==0)) //first i/p is -ve &2nd is +ve
		begin
		  aa=(~a)+16'h0001;  //2's comp to make it +ve
		  temp=aa*b; //now (+ve * +ve)
		  //temp=temp+sign;
		  temp=(~temp)+16'h0001;//convert it to negative as supposed to be
		  out=temp[int_upper:fraction];
		end
		else if ((b[15]==1) && (a[15]==0)) //first i/p is +ve &2nd is -ve
      begin
		  bb=(~b)+16'h0001;  //2's comp to make it +ve
		  temp=a*bb;
		  temp=(~temp)+16'h0001;//convert it to negative as supposed to be
		  out=temp[int_upper:fraction];		  
		end
		else if ((b[15]==1) && (a[15]==1)) //both inputs are -ve
		begin
        aa=(~a)+16'h0001;
		  bb=(~b)+16'h0001;
		  temp=aa*bb;
		  out=temp[int_upper:fraction];
		end
     	else
		begin
		  temp=a*b; //according to # int & fractions we keep only the int before and after the point
		  out=temp[int_upper:fraction];
		end
  end	  
endtask
  
endmodule
