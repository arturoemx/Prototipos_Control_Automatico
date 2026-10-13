##Ejecución del graficador en tiempo real
Para ejecutar el programa **PID.py** en Linux se debe de crear un entorno virtual para realizarlo sin
romper nada del sistema operativo ya que este se encuentra escrito en su mayoría por Python, para evitar conflictos de
librerías y mantener un mejor control de los paquetes usados se realizará todo mediante un entorno virtual

**Primero se actualizan los repositorios y se instala el paquete** python3-venv
`sudo apt update`
`sudo apt install python3-venv`
**`apt`** es el gestor de paquetes que usan las distribuciones basadas en Debian, si se usa otra
distribución basta con cambiar `apt` por el gestor que se use en realidad.
**Se navega** al directorio donde se van a **ejecutar los programas**.
`cd ruta/al/directorio`
**Se crea** el entorno virtual con el comando `python3 -m venv mi_entorno`
Se puede cambiar `mi_entorno` por otro nombre
**Se activa** el entorno virtual con el comando `source mi_entorno/bin/activate`
Dentro de este entorno se puede ahora instalar los paquetes necesarios con la herramienta `pip`
Se instalarán los paquetes **pyserial** y **matplotlib**.
`pip install pyserial`
`pip install matplotlib`
Finalmente se ejecuta `python3 PID.py` para ver el graficador en tiempo real.
Para desactivar el entorno virtual se ejecuta el comando `deactivate`.

