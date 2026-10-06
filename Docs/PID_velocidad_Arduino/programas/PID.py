import serial
import matplotlib.pyplot as plt
import matplotlib.animation as animation

# CONFIGURACIÓN SERIAL
ser = serial.Serial('/dev/ttyACM0', 115200, timeout=1)

# LISTAS PARA GUARDAR LOS DATOS
tiempos = []
referencias = []
rpms = []
pwm_s = []
errores = []

# CONFIGURAR GRÁFICA
fig, ax = plt.subplots()
line_ref, = ax.plot([], [], label='Referencia (RPM)', color='green')
line_rpm, = ax.plot([], [], label='Velocidad real (RPM)', color='blue')
line_pwm, = ax.plot([], [], label='PWM', color='red')
line_err, = ax.plot([], [], label='Error', color='orange')

ax.set_title('Control PID en Tiempo Real')
ax.set_xlabel('Tiempo (ms)')
ax.set_ylabel('Valores')
ax.grid(True)
ax.legend()

# ACTUALIZAR GRÁFICA
def update(frame):
    while ser.in_waiting:
        try:
            linea = ser.readline().decode('utf-8').strip()
            datos = linea.split(',')

            if len(datos) != 7:
                return

            t = int(datos[0])
            ref = float(datos[1])
            rpm = float(datos[2])
            pwm = int(datos[3])
            err = float(datos[4])

            # Guardar datos
            tiempos.append(t)
            referencias.append(ref)
            rpms.append(rpm)
            pwm_s.append(pwm)
            errores.append(err)

            # Mantener solo los últimos 200 puntos
            if len(tiempos) > 200:
                tiempos.pop(0)
                referencias.pop(0)
                rpms.pop(0)
                pwm_s.pop(0)
                errores.pop(0)

            # Actualizar líneas
            line_ref.set_data(tiempos, referencias)
            line_rpm.set_data(tiempos, rpms)
            line_pwm.set_data(tiempos, pwm_s)
            line_err.set_data(tiempos, errores)

            ax.relim()
            ax.autoscale_view()

        except Exception as e:
            print(f"Error: {e}")

    return line_ref, line_rpm, line_pwm, line_err

ani = animation.FuncAnimation(fig, update, interval=50, cache_frame_data=False)
plt.tight_layout()
plt.show()




