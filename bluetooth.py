import serial
import pygame
import time

print("Start")

port="COM4" #This will be different for various devices and on windows it will probably be a COM port.
bluetooth=serial.Serial(port, 115200)#Start communications with the bluetooth unit
print("Connected")

# Inizializza Pygame
pygame.init()

# Configura la finestra
window_size = (400, 400)
window = pygame.display.set_mode(window_size)
pygame.display.set_caption("Bluetooth")

# Definisce i colori
white = (255, 255, 255)
black = (0, 0, 0)

# Definisce i font
font = pygame.font.Font(None, 36)

# Definisce i bottoni
button1_rect = pygame.Rect(50, 50, 100, 50)
button2_rect = pygame.Rect(250, 50, 100, 50)

# Disegna i bottoni sulla finestra
pygame.draw.rect(window, white, button1_rect)
pygame.draw.rect(window, white, button2_rect)

# Aggiorna la finestra
pygame.display.update()

# Loop principale
while True:
    # Gestione degli eventi
    for event in pygame.event.get():
        if event.type == pygame.QUIT: # l'utente ha cliccato la X
            bluetooth.close()
            pygame.quit()
            quit()
        elif event.type == pygame.MOUSEBUTTONDOWN: # l'utente ha cliccato un pulsante del mouse
            if button1_rect.collidepoint(event.pos): # l'utente ha cliccato il primo pulsante
                data="Accendi "
                bluetooth.write(data.encode())
            elif button2_rect.collidepoint(event.pos): # l'utente ha cliccato il secondo pulsante
                data="Spegni "
                bluetooth.write(data.encode())

    # Aggiorna la finestra
    window.fill(black)
    pygame.draw.rect(window, white, button1_rect)
    pygame.draw.rect(window, white, button2_rect)
    text1 = font.render("Accendi", True, black)
    text2 = font.render("Spegni", True, black)
    window.blit(text1, (button1_rect.centerx - text1.get_width() // 2, button1_rect.centery - text1.get_height() // 2))
    window.blit(text2, (button2_rect.centerx - text2.get_width() // 2, button2_rect.centery - text2.get_height() // 2))
    pygame.display.update()
