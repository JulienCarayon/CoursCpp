from PIL import Image
import re

def decode_text_in_image(image_path):
    # Ouvre l'image en mode lecture
    img = Image.open(image_path)
    # Convertit le message en une chaîne binaire
    # message_bin = ''.join(format(ord(c), '08b') for c in message)
    message = ""
    # Vérifie si le message est trop long pour être caché dans l'image
    # Cachage du message dans les pixels de l'image
    pixels = img.load()
    index = 0

    bits = ""
    counter8bit=0
    message_prefix=''

    actual_char=0

    for y in range(img.height):
        for x in range(img.width):
            counter8bit+=1
            pixel = pixels[x, y]
            r = pixel[0] & 1
            # print(f"LSB: {r}" )
            bits+=str(r)
            
            if counter8bit == 8:
                bit = int(bits, 2)
                # print(f"BIT: {bit}")
                char = str(chr(bit))
                # print(f"char: {char}")
                message+=char
                bits=''
                counter8bit=0
                actual_char+=1
            m = re.search('\[(\d*)\]', message)
            if m is not None:
                # print(m.group(0))
                message_prefix = m.group(0)
                message_length=int(m.group(1))
                if actual_char>=message_length+len(message_prefix):
                    break

                
    message = message.replace(message_prefix,'')[0:message_length]    
    return message

# Exemple d'utilisation
# print(f"TEST : {format(ord('C'), '08b')}")
image_path = "image_avec_message.png"
print(f"MESSAGE : {decode_text_in_image(image_path)}")
