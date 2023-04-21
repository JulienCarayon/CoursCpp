from PIL import Image

def hide_text_in_image(image_path, message):
    # Ouvre l'image en mode lecture
    img = Image.open(image_path)
    # Convertit le message en une chaîne binaire
    message_bin = ''.join(format(ord(c), '08b') for c in message)
    message=f'[{len(message)}]'+message
    message_bin = ''.join(format(ord(c), '08b') for c in message)
    print(message)
    

    # Vérifie si le message est trop long pour être caché dans l'image
    if len(message_bin) > img.width * img.height:
        raise ValueError("Le message est trop long pour être caché dans l'image.")
    # Cachage du message dans les pixels de l'image
    pixels = img.load()
    index = 0
    for y in range(img.height):
        for x in range(img.width):
            if index < len(message_bin):
                pixel = pixels[x, y]
                r = pixel[0]
                # Remplace le bit de poids faible de chaque canal de couleur par un bit du message
                pixels[x, y] = (r & ~1 | int(message_bin[index]))
                index +=1
            else:
                break
    # Enregistre l'image modifiée avec le message caché
    img.save("../Decrypt_cpp/image_avec_message.png")

# Exemple d'utilisation
image_path = "img.png"
message = "Chiens qui baisent"
hide_text_in_image(image_path, message)
