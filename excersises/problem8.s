.text

li x10,0x53 //dir reg A
li x11,0x54 //dir reg B
li x12,0x55 //dir reg C

//a

//lee el registro A
lbu x20, 0(x10)
//Aplica una mascara al bit 4-> 0001 0000
andi x20, x20, 0x10
//Desplazas (sifht  right logical inmediate) el bit 4 a la posicion bit 1
srli x20, x20, 3
//lees el registro B
lbu x21, 0(x11)
// Y activas en el registro B el bit 1
or x21, x21, x20
//se lo enviars al registor B
sbu x21, 0(x11)

//Mi optimización asume el estado estático del enunciado 
//(donde el bit 4 de Reg A es un '1' fijo). Si el bit 4 de Reg 
//A pudiera cambiar dinámicamente entre '0' y '1' en el tiempo, sí se necesitaría 
//el código original para replicar su estado en Reg B

lbu x21, 0(x11)
ori x21,x21, 0x02
sbu x21, 0(x11)

//b

//verion optimizada
lbu x22, 0(x12)
ori x22,x22, 0x40
sbu x22, 0(x12)

//versin examen

lbu x20, 0(x10)
andi x20, x20, 0x10
slli x20, x20, 2
lbu x22, 0(x12)
or x22, x22, x20
sbu x22, 0(x12)


//c

lbu x22,0(x12)
add x23, x22, x0 
andi x23,x23,0x04
beqz x23, setone

andi x22, x22, 0xFB
sbu x22, 0x(x12)
j finc

setone:

addi x22, x22, 0x04
sbu x22, 0x(x12)

finc: