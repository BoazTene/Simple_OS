ENTRY(_start)

SECTIONS
{
  . = 0x6000;
  .text : ALIGN(0x1000) 
  {
      *(.text)
   }

   .data : {
      *(.data)
   }
}