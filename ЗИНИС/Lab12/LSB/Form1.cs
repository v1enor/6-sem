
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Collections;

namespace StegProject
{

    public partial class Form1 : Form
    {

        public int len = 1;
        public int CountText = 0;

        public Form1()
        {
            InitializeComponent();
        }

        private BitArray ByteToBit(byte src)
        {
            BitArray bitArray = new BitArray(8);
            bool st = false;
            for (int i = 0; i < 8; i++)
            {
                if ((src >> i & 1) == 1)
                {
                    st = true;
                }
                else st = false;
                bitArray[i] = st;
            }
            return bitArray;
        }

        private byte BitToByte(BitArray scr)
        {
            byte num = 0;
            for (int i = 0; i < scr.Count; i++)
                if (scr[i] == true)
                    num += (byte)Math.Pow(2, i);
            return num;
        }

        // Проверяет, зашифрован ли файл,  возвраещает true, если символ в первом пикслеле равен / иначе false
        private bool isEncryption(Bitmap scr)
        {
            byte[] rez = new byte[1];
            Color color = scr.GetPixel(0, 0);
            BitArray colorArray = ByteToBit(color.R); //получаем байт цвета и преобразуем в массив бит
            BitArray messageArray = ByteToBit(color.R); ;//инициализируем результирующий массив бит
            messageArray[0] = colorArray[0];
            messageArray[1] = colorArray[1];

            colorArray = ByteToBit(color.G);//получаем байт цвета и преобразуем в массив бит
            messageArray[2] = colorArray[0];
            messageArray[3] = colorArray[1];
            messageArray[4] = colorArray[2];

            colorArray = ByteToBit(color.B);//получаем байт цвета и преобразуем в массив бит
            messageArray[5] = colorArray[0];
            messageArray[6] = colorArray[1];
            messageArray[7] = colorArray[2];
            rez[0] = BitToByte(messageArray); //получаем байт символа, записанного в 1 пикселе
            string m = Encoding.GetEncoding(1251).GetString(rez);
            if (m == "E")
            {
                return true;
            }
            else return false;
        }

        // Записыает количество символов для шифрования в первые биты картинки
        private void WriteCountText(int count, Bitmap src)
        {
            byte[] CountSymbols = Encoding.GetEncoding(1251).GetBytes(count.ToString());
            for (int i = 0; i < CountSymbols.Length; i++)
            {
                BitArray bitCount = ByteToBit(CountSymbols[i]); //биты количества символов
                Color pColor = src.GetPixel(0, i + 1); //1, 2, 3 пикселы
                BitArray bitsCurColor = ByteToBit(pColor.R); //бит цветов текущего пикселя
                bitsCurColor[0] = bitCount[0];
                bitsCurColor[1] = bitCount[1];
                byte nR = BitToByte(bitsCurColor); //новый бит цвета пиксея

                bitsCurColor = ByteToBit(pColor.G);//бит бит цветов текущего пикселя
                bitsCurColor[0] = bitCount[2];
                bitsCurColor[1] = bitCount[3];
                bitsCurColor[2] = bitCount[4];
                byte nG = BitToByte(bitsCurColor);//новый цвет пиксея

                bitsCurColor = ByteToBit(pColor.B);//бит бит цветов текущего пикселя
                bitsCurColor[0] = bitCount[5];
                bitsCurColor[1] = bitCount[6];
                bitsCurColor[2] = bitCount[7];
                byte nB = BitToByte(bitsCurColor);//новый цвет пиксея

                Color nColor = Color.FromArgb(nR, nG, nB); //новый цвет из полученных битов
                src.SetPixel(0, i + 1, nColor); //записали полученный цвет в картинку
            }
        }


        // Открыть файл для шифрования
        private void write_Click(object sender, EventArgs e)
        {
            if (radioButton1.Checked == true || radioButton2.Checked == true)
            {

                string FilePic;
                string FileText;
                OpenFileDialog dPic = new OpenFileDialog();
                dPic.Filter = "Файлы изображений (*.bmp)|*.bmp|Все файлы (*.*)|*.*";
                if (dPic.ShowDialog() == DialogResult.OK)
                {
                    FilePic = dPic.FileName;
                }
                else
                {
                    FilePic = "";
                    return;
                }

                FileStream rFile;
                try
                {
                    rFile = new FileStream(FilePic, FileMode.Open); //открываем поток
                }
                catch (IOException)
                {
                    MessageBox.Show("Ошибка открытия файла", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
                Bitmap bPic = new Bitmap(rFile);

                Bitmap bPicR1 = new Bitmap(rFile);
                Bitmap bPicR2 = new Bitmap(rFile);
                Bitmap bPicR3 = new Bitmap(rFile);
                Bitmap bPicR4 = new Bitmap(rFile);


                OpenFileDialog dText = new OpenFileDialog();
                dText.Filter = "Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*";
                if (dText.ShowDialog() == DialogResult.OK)
                {
                    FileText = dText.FileName;
                }
                else
                {
                    FileText = "";
                    return;
                }

                using (StreamReader sr = new StreamReader(FileText))
                {
                    string sod = sr.ReadToEnd();
                    len = sod.Length;
                }

                FileStream rText;
                try
                {
                    rText = new FileStream(FileText, FileMode.Open); //открываем поток
                }
                catch (IOException)
                {
                    MessageBox.Show("Ошибка открытия файла", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }

                BinaryReader bText = new BinaryReader(rText, Encoding.ASCII);

                List<byte> bList = new List<byte>();
                while (bText.PeekChar() != -1)
                { //считали весь текстовый файл для шифрования в лист байт
                    bList.Add(bText.ReadByte());
                }
                CountText = bList.Count; // в CountText - количество в байтах текста, который нужно закодировать
                bText.Close();
                rFile.Close();

                //проверяем, поместиться ли исходный текст в картинке
                if (CountText > (bPic.Width * bPic.Height))
                {
                    MessageBox.Show("Выбранная картинка мала для размещения выбранного текста");
                    return;
                }

                //проверяем, может быть картинка уже зашифрована
                if (isEncryption(bPic))
                {
                    MessageBox.Show("Файл уже зашифрован");
                    return;
                }

                // записываем в пиксель 0.0 признак зашифрованного файла
                byte[] Symbol = Encoding.GetEncoding(1251).GetBytes("E");
                BitArray ArrBeginSymbol = ByteToBit(Symbol[0]);
                Color curColor = bPic.GetPixel(0, 0);
                BitArray tempArray = ByteToBit(curColor.R);
                tempArray[0] = ArrBeginSymbol[0];
                tempArray[1] = ArrBeginSymbol[1];
                byte nR = BitToByte(tempArray);

                tempArray = ByteToBit(curColor.G);
                tempArray[0] = ArrBeginSymbol[2];
                tempArray[1] = ArrBeginSymbol[3];
                tempArray[2] = ArrBeginSymbol[4];
                byte nG = BitToByte(tempArray);

                tempArray = ByteToBit(curColor.B);
                tempArray[0] = ArrBeginSymbol[5];
                tempArray[1] = ArrBeginSymbol[6];
                tempArray[2] = ArrBeginSymbol[7];
                byte nB = BitToByte(tempArray);

                Color nColor = Color.FromArgb(nR, nG, nB);

                bPic.SetPixel(0, 0, nColor);

                //записываем количество символов для шифрования
                WriteCountText(CountText, bPic);

               

                if (radioButton1.Checked == true)
                {
                    //записываем инфу в контейнер
                    int index = 0;
                    bool st = false;
                    for (int i = 0; i < bPic.Width; i++)
                    {
                        for (int j = 1; j < bPic.Height; j++)
                        {
                            Color pixelColor = bPic.GetPixel(i, j);
                            if (index == bList.Count)
                            {
                                st = true;
                                break;
                            }
                            BitArray colorArray = ByteToBit(pixelColor.R);
                            byte Rtemp = 0;
                            byte Rtemp2 = 0;
                            if (colorArray[0] == true)
                            {
                                Rtemp = 255;
                            }
                            else
                            {
                                Rtemp = 0;
                            }
                            if (colorArray[1] == true)
                            {
                                Rtemp2 = 255;
                            }
                            else
                            {
                                Rtemp2 = 0;
                            }
                            BitArray messageArray = ByteToBit(bList[index]);
                            colorArray[0] = messageArray[0]; //меняем
                            colorArray[1] = messageArray[1]; // в нашем цвете биты
                            byte Rtemp3 = 0;
                            byte Rtemp4 = 0;
                            if (colorArray[0] == true)
                            {
                                Rtemp3 = 255;
                            }
                            else
                            {
                                Rtemp3 = 0;
                            }
                            if (colorArray[1] == true)
                            {
                                Rtemp4 = 255;
                            }
                            else
                            {
                                Rtemp4 = 0;
                            }
                            byte newR = BitToByte(colorArray);

                            colorArray = ByteToBit(pixelColor.G);
                            byte Gtemp = 0;
                            byte Gtemp2 = 0;
                            if (colorArray[0] == true)
                            {
                                Gtemp = 255;
                            }
                            else
                            {
                                Gtemp = 0;
                            }
                            if (colorArray[1] == true)
                            {
                                Gtemp2 = 255;
                            }
                            else
                            {
                                Gtemp2 = 0;
                            }
                            colorArray[0] = messageArray[2];
                            colorArray[1] = messageArray[3];
                            colorArray[2] = messageArray[4];
                            byte Gtemp3 = 0;
                            byte Gtemp4 = 0;
                            if (colorArray[0] == true)
                            {
                                Gtemp3 = 255;
                            }
                            else
                            {
                                Gtemp3 = 0;
                            }
                            if (colorArray[1] == true)
                            {
                                Gtemp4 = 255;
                            }
                            else
                            {
                                Gtemp4 = 0;
                            }
                            byte newG = BitToByte(colorArray);

                            colorArray = ByteToBit(pixelColor.B);
                            byte Btemp = 0;
                            byte Btemp2 = 0;
                            if (colorArray[0] == true)
                            {
                                Btemp = 255;
                            }
                            else
                            {
                                Btemp = 0;
                            }
                            if (colorArray[1] == true)
                            {
                                Btemp2 = 255;
                            }
                            else
                            {
                                Btemp2 = 0;
                            }
                            colorArray[0] = messageArray[5];
                            colorArray[1] = messageArray[6];
                            colorArray[2] = messageArray[7];
                            byte Btemp3 = 0;
                            byte Btemp4 = 0;
                            if (colorArray[0] == true)
                            {
                                Btemp3 = 255;
                            }
                            else
                            {
                                Btemp3 = 0;
                            }
                            if (colorArray[1] == true)
                            {
                                Btemp4 = 255;
                            }
                            else
                            {
                                Btemp4 = 0;
                            }
                            byte newB = BitToByte(colorArray);

                            Color newColor = Color.FromArgb(newR, newG, newB);

                            Color newMatrixColor= Color.FromArgb(Rtemp, Gtemp, Btemp);
                            Color newMatrixColor2 = Color.FromArgb(Rtemp2, Gtemp2, Btemp2);
                            Color newMatrixColor3 = Color.FromArgb(Rtemp3, Gtemp3, Btemp3);
                            Color newMatrixColor4 = Color.FromArgb(Rtemp4, Gtemp4, Btemp4);

                            bPic.SetPixel(i, j, newColor);

                            bPicR1.SetPixel(i,j, newMatrixColor);
                            bPicR2.SetPixel(i, j, newMatrixColor2);
                            bPicR3.SetPixel(i, j, newMatrixColor3);
                            bPicR4.SetPixel(i, j, newMatrixColor4);
                            index++;
                        }
                        if (st)
                        {
                            break;
                        }
                    }
                }
                else
                {
                    int index = 0;
                    bool st = false;
                    for (int i = 0; i < bPic.Height; i++)
                    {
                        for (int j = 1; j < bPic.Width; j++)
                        {
                            Color pixelColor = bPic.GetPixel(j, i);
                            if (index == bList.Count)
                            {
                                st = true;
                                break;
                            }
                            BitArray colorArray = ByteToBit(pixelColor.R);
                            byte Rtemp = 0;
                            byte Rtemp2 = 0;
                            if (colorArray[0] == true)
                            {
                                Rtemp = 255;
                            }
                            else
                            {
                                Rtemp = 0;
                            }
                            if (colorArray[1] == true)
                            {
                                Rtemp2 = 255;
                            }
                            else
                            {
                                Rtemp2 = 0;
                            }
                            BitArray messageArray = ByteToBit(bList[index]);
                            colorArray[0] = messageArray[0]; //меняем
                            colorArray[1] = messageArray[1]; // в нашем цвете биты
                            byte Rtemp3 = 0;
                            byte Rtemp4 = 0;
                            if (colorArray[0] == true)
                            {
                                Rtemp3 = 255;
                            }
                            else
                            {
                                Rtemp3 = 0;
                            }
                            if (colorArray[1] == true)
                            {
                                Rtemp4 = 255;
                            }
                            else
                            {
                                Rtemp4 = 0;
                            }
                            byte newR = BitToByte(colorArray);

                            colorArray = ByteToBit(pixelColor.G);
                            byte Gtemp = 0;
                            byte Gtemp2 = 0;
                            if (colorArray[0] == true)
                            {
                                Gtemp = 255;
                            }
                            else
                            {
                                Gtemp = 0;
                            }
                            if (colorArray[1] == true)
                            {
                                Gtemp2 = 255;
                            }
                            else
                            {
                                Gtemp2 = 0;
                            }
                            colorArray[0] = messageArray[2];
                            colorArray[1] = messageArray[3];
                            colorArray[2] = messageArray[4];
                            byte Gtemp3 = 0;
                            byte Gtemp4 = 0;
                            if (colorArray[0] == true)
                            {
                                Gtemp3 = 255;
                            }
                            else
                            {
                                Gtemp3 = 0;
                            }
                            if (colorArray[1] == true)
                            {
                                Gtemp4 = 255;
                            }
                            else
                            {
                                Gtemp4 = 0;
                            }
                            byte newG = BitToByte(colorArray);

                            colorArray = ByteToBit(pixelColor.B);
                            byte Btemp = 0;
                            byte Btemp2 = 0;
                            if (colorArray[0] == true)
                            {
                                Btemp = 255;
                            }
                            else
                            {
                                Btemp = 0;
                            }
                            if (colorArray[1] == true)
                            {
                                Btemp2 = 255;
                            }
                            else
                            {
                                Btemp2 = 0;
                            }
                            colorArray[0] = messageArray[5];
                            colorArray[1] = messageArray[6];
                            colorArray[2] = messageArray[7];
                            byte Btemp3 = 0;
                            byte Btemp4 = 0;
                            if (colorArray[0] == true)
                            {
                                Btemp3 = 255;
                            }
                            else
                            {
                                Btemp3 = 0;
                            }
                            if (colorArray[1] == true)
                            {
                                Btemp4 = 255;
                            }
                            else
                            {
                                Btemp4 = 0;
                            }
                            byte newB = BitToByte(colorArray);

                            Color newColor = Color.FromArgb(newR, newG, newB);

                            Color newMatrixColor = Color.FromArgb(Rtemp, Gtemp, Btemp);
                            Color newMatrixColor2 = Color.FromArgb(Rtemp2, Gtemp2, Btemp2);
                            Color newMatrixColor3 = Color.FromArgb(Rtemp3, Gtemp3, Btemp3);
                            Color newMatrixColor4 = Color.FromArgb(Rtemp4, Gtemp4, Btemp4);

                            bPic.SetPixel(j, i, newColor);

                            bPicR1.SetPixel(j, i, newMatrixColor);
                            bPicR2.SetPixel(j, i, newMatrixColor2);
                            bPicR3.SetPixel(j, i, newMatrixColor3);
                            bPicR4.SetPixel(j, i, newMatrixColor4);
                            index++;
                        }
                        if (st)
                        {
                            break;
                        }
                    }
                }
                pictureBox1.Image = bPic;
                pictureBox2.Image = bPicR1;
                pictureBox3.Image = bPicR2;
                pictureBox4.Image = bPicR3;
                pictureBox5.Image = bPicR4;

                String sFilePic;
                SaveFileDialog dSavePic = new SaveFileDialog();
                dSavePic.Filter = "Файлы изображений (*.bmp)|*.bmp|Все файлы (*.*)|*.*";
                if (dSavePic.ShowDialog() == DialogResult.OK)
                {
                    sFilePic = dSavePic.FileName;
                }
                else
                {
                    sFilePic = "";
                    return;
                };

                FileStream wFile;
                try
                {
                    wFile = new FileStream(sFilePic, FileMode.Create); //открываем поток на запись результатов
                }
                catch (IOException)
                {
                    MessageBox.Show("Ошибка открытия файла на запись", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }

                bPic.Save(wFile, System.Drawing.Imaging.ImageFormat.Bmp);
                wFile.Close(); //закрываем поток
            }
            else
            {
                MessageBox.Show("Ошибка Выполнения. Выберите способ осаждения!", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }





        // Открыть файл для дешифрования
        private void read_Click(object sender, EventArgs e)
        {
            if (radioButton1.Checked == true || radioButton2.Checked == true)
            {
                string FilePic;
                OpenFileDialog dPic = new OpenFileDialog();
                dPic.Filter = "Файлы изображений (*.bmp)|*.bmp|Все файлы (*.*)|*.*";
                if (dPic.ShowDialog() == DialogResult.OK)
                {
                    FilePic = dPic.FileName;
                }
                else
                {
                    FilePic = "";
                    return;
                }

                FileStream rFile;
                try
                {
                    rFile = new FileStream(FilePic, FileMode.Open); //открываем поток
                }
                catch (IOException)
                {
                    MessageBox.Show("Ошибка открытия файла", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
                Bitmap bPic = new Bitmap(rFile);
                if (!isEncryption(bPic))
                {
                    MessageBox.Show("В файле нет зашифрованной информации", "Информация", MessageBoxButtons.OK);
                    return;
                }

                //считали количество зашифрованных символов
                int countSymbol = bPic.Width*bPic.Height-1;

                byte[] message = new byte[countSymbol];
                //считываем текст из стеганосообщения
                if (radioButton1.Checked == true)
                {
                    
                    int index = 0;
                    bool st = false;
                    for (int i = 0; i < bPic.Width; i++)
                    {
                        for (int j = 1; j < bPic.Height; j++)
                        {
                            Color pixelColor = bPic.GetPixel(i, j);
                            if (index == message.Length)
                            {
                                st = true;
                                break;
                            }
                            BitArray colorArray = ByteToBit(pixelColor.R);
                            BitArray messageArray = ByteToBit(pixelColor.R); ;
                            messageArray[0] = colorArray[0];
                            messageArray[1] = colorArray[1];

                            colorArray = ByteToBit(pixelColor.G);
                            messageArray[2] = colorArray[0];
                            messageArray[3] = colorArray[1];
                            messageArray[4] = colorArray[2];

                            colorArray = ByteToBit(pixelColor.B);
                            messageArray[5] = colorArray[0];
                            messageArray[6] = colorArray[1];
                            messageArray[7] = colorArray[2];
                            message[index] = BitToByte(messageArray);
                            index++;
                        }
                        if (st) break;
                    }
                }
                else
                {
                    int index = 0;
                    bool st = false;
                    for (int i = 0; i < bPic.Height-1; i++)
                    {
                        for (int j = 1; j < bPic.Width-1; j++)
                        {
                            Color pixelColor = bPic.GetPixel(j, i);
                            if (index == message.Length)
                            {
                                st = true;
                                break;
                            }
                            BitArray colorArray = ByteToBit(pixelColor.R);
                            BitArray messageArray = ByteToBit(pixelColor.R); ;
                            messageArray[0] = colorArray[0];
                            messageArray[1] = colorArray[1];

                            colorArray = ByteToBit(pixelColor.G);
                            messageArray[2] = colorArray[0];
                            messageArray[3] = colorArray[1];
                            messageArray[4] = colorArray[2];

                            colorArray = ByteToBit(pixelColor.B);
                            messageArray[5] = colorArray[0];
                            messageArray[6] = colorArray[1];
                            messageArray[7] = colorArray[2];
                            message[index] = BitToByte(messageArray);
                            index++;
                        }
                        if (st) break;
                    }
                }
                string strMessage = Encoding.GetEncoding(1251).GetString(message);
                //strMessage = strMessage.Substring(0, len*2+2);
                strMessage = strMessage.Substring(0, CountText);

                string sFileText;
                SaveFileDialog dSaveText = new SaveFileDialog();
                dSaveText.Filter = "Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*";
                if (dSaveText.ShowDialog() == DialogResult.OK)
                {
                    sFileText = dSaveText.FileName;
                }
                else
                {
                    sFileText = "";
                    return;
                };

                FileStream wFile;
                try
                {
                    wFile = new FileStream(sFileText, FileMode.Create); //открываем поток на запись результатов
                }
                catch (IOException)
                {
                    MessageBox.Show("Ошибка открытия файла на запись", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
                StreamWriter wText = new StreamWriter(wFile, Encoding.Default);
                wText.Write(strMessage);
                MessageBox.Show("Сообщение извлечено в файл!", "Информация", MessageBoxButtons.OK);
                wText.Close();
                wFile.Close(); //закрываем поток

            }
            else
            {
                MessageBox.Show("Ошибка Выполнения. Выберите способ Чтения!", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
       
    }
}
