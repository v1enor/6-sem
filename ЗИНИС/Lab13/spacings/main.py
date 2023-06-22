import stegospacings

stegospacings.encode('ilusha', 'container.docx', 'encoded.docx')
print(stegospacings.decode('encoded.docx'))
