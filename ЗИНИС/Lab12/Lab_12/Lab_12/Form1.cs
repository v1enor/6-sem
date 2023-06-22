using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab_12
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        string[,] redArr = new string[256, 256];
        string[,] greenArr = new string[256, 256];
        string[,] blueArr = new string[256, 256];
        int count = 0;

        private int binToDec(string bin)
        {
            return 128 * Convert.ToInt32(bin[0].ToString()) +
                   64 * Convert.ToInt32(bin[1].ToString()) +
                   32 * Convert.ToInt32(bin[2].ToString()) +
                   16 * Convert.ToInt32(bin[3].ToString()) +
                   8 * Convert.ToInt32(bin[4].ToString()) +
                   4 * Convert.ToInt32(bin[5].ToString()) +
                   2 * Convert.ToInt32(bin[6].ToString()) +
                   1 * Convert.ToInt32(bin[7].ToString());
        }

        private void openFile_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Image Files (*.png, *.jpg) | *.png; *.jpg";
            openFileDialog.InitialDirectory = @"D:\Crypto\Part 2\Lab_12\Lab_12\Lab_12\bin\Debug";

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                Bitmap originalBitmap = new Bitmap(openFileDialog.FileName);
                originalImage.Image = originalBitmap;

                for (int y = 0; y < 256; y++)
                {
                    for (int x = 0; x < 256; x++)
                    {
                        redArr[x, y] = Convert.ToString(originalBitmap.GetPixel(x, y).R, 2).PadLeft(8, '0');
                        greenArr[x, y] = Convert.ToString(originalBitmap.GetPixel(x, y).G, 2).PadLeft(8, '0');
                        blueArr[x, y] = Convert.ToString(originalBitmap.GetPixel(x, y).B, 2).PadLeft(8, '0');
                    }
                }

                Bitmap redBitmap = new Bitmap(256, 256);
                Bitmap greenBitmap = new Bitmap(256, 256);
                Bitmap blueBitmap = new Bitmap(256, 256);
                Bitmap colorBitmap = new Bitmap(256, 256);
                for (int y = 0; y < 256; y++)
                {
                    for (int x = 0; x < 256; x++)
                    {
                        if (redArr[x, y][7] == '0') redBitmap.SetPixel(x, y, Color.White);
                        else redBitmap.SetPixel(x, y, Color.Black);

                        if (greenArr[x, y][7] == '0') greenBitmap.SetPixel(x, y, Color.White);
                        else greenBitmap.SetPixel(x, y, Color.Black);

                        if (blueArr[x, y][7] == '0') blueBitmap.SetPixel(x, y, Color.White);
                        else blueBitmap.SetPixel(x, y, Color.Black);

                        colorBitmap.SetPixel(x, y, Color.FromArgb(Convert.ToInt32(redArr[x, y][7].ToString()) * 255, Convert.ToInt32(greenArr[x, y][7].ToString()) * 255, Convert.ToInt32(blueArr[x, y][7].ToString()) * 255));
                    }
                }
                redImage.Image = redBitmap;
                greenImage.Image = greenBitmap;
                blueImage.Image = blueBitmap;
                colorImage.Image = colorBitmap;            }
        }

        private void stegButton_Click(object sender, EventArgs e)
        {
            string steg = stegText.Text;
            byte[] byteAscii = Encoding.ASCII.GetBytes(steg);
            string text = "";
            for (int i = 0; i < steg.Length; i++)
            {
                text += Convert.ToString(byteAscii[i], 2).PadLeft(8, '0');
            }

            for (int y = 0; y < 256; y++)
            {
                for (int x = 0; x < 256; x++)
                {
                    redArr[x, y] = redArr[x, y].Substring(0, 7).PadRight(8, '0');
                    greenArr[x, y] = greenArr[x, y].Substring(0, 7).PadRight(8, '0');
                    blueArr[x, y] = blueArr[x, y].Substring(0, 7).PadRight(8, '0');
                }
            }

            count = text.Length;
            count = (((count - 1) / 3) * 3) + 3;
            text.PadRight(count, '0');

            for (int i = 0; i < text.Length / 3; i++)
            {
                int x = i % 256;
                int y = i / 256;
                redArr[x, y] = redArr[x, y].Substring(0, 7) + text[i * 3];
                greenArr[x, y] = greenArr[x, y].Substring(0, 7) + text[i * 3 + 1];
                blueArr[x, y] = blueArr[x, y].Substring(0, 7) + text[i * 3 + 2];
            }

            Bitmap resultBitmap = new Bitmap(256, 256);
            for (int y = 0; y < 256; y++)
            {
                for (int x = 0; x < 256; x++)
                {
                    resultBitmap.SetPixel(x, y, Color.FromArgb(binToDec(redArr[x, y]), binToDec(greenArr[x, y]), binToDec(blueArr[x, y])));
                }
            }
            stegImage.Image = resultBitmap;
            resultBitmap.Save("steganograpy.png", System.Drawing.Imaging.ImageFormat.Png);
        }

        private void deStegOpenFile_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Image Files (*.png, *.jpg) | *.png; *.jpg";
            openFileDialog.InitialDirectory = @"D:\Crypto\Part 2\Lab_12\Lab_12\Lab_12\bin\Debug";

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                Bitmap deStegBitmap = new Bitmap(openFileDialog.FileName);
                deStegImage.Image = deStegBitmap;

                for (int y = 0; y < 256; y++)
                {
                    for (int x = 0; x < 256; x++)
                    {
                        redArr[x, y] = Convert.ToString(deStegBitmap.GetPixel(x, y).R, 2).PadLeft(8, '0');
                        greenArr[x, y] = Convert.ToString(deStegBitmap.GetPixel(x, y).G, 2).PadLeft(8, '0');
                        blueArr[x, y] = Convert.ToString(deStegBitmap.GetPixel(x, y).B, 2).PadLeft(8, '0');
                    }
                }

                string text = "";
                for (int i = 0; i < 1000; i++)
                {
                    int x = i % 256;
                    int y = i / 256;
                    text += redArr[x, y][7].ToString() + greenArr[x, y][7].ToString() + blueArr[x, y][7].ToString();
                }

                count = text.Length;
                count = (((count - 1) / 8) * 8) + 8;
                text.PadRight(count, '0');

                var result = "";
                for (int i = 0; i < count / 8 - 1; i++)
                {
                    result += (char)binToDec(text.Substring(8 * i, 8));
                }
                deStegText.Text = result;
            }
        }
    }
}
