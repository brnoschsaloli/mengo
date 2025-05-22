; ModuleID = 'mengo.bc'
source_filename = "mengo"

@x = global double 0.000000e+00
@y = global double 0.000000e+00
@format = private unnamed_addr constant [4 x i8] c"%f\0A\00", align 1

define void @main() {
entry:
  store double 1.050000e+01, double* @x, align 8
  %loadtmp = load double, double* @x, align 8
  %addtmp = fadd double %loadtmp, 5.000000e+00
  store double %addtmp, double* @y, align 8
  %loadtmp1 = load double, double* @y, align 8
  %0 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @format, i32 0, i32 0), double %loadtmp1)
  ret void
}

declare i32 @printf(i8*, ...)
