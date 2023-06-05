using GalaSoft.MvvmLight.Command;
using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;
using ZinizCourceProject.Model;

namespace ZinizCourceProject.ViewModel
{
    

    internal class AESViewModel:INotifyPropertyChanged
    {

        public string SomeState { get; set; }

        private string _plainText = "Сообщение";
        private string _cipherText = "Шифр Текст";
        private string _key = "Ключ";
        private readonly byte[] IV = new byte[16]; // 16 байт = 128 бит

        public event PropertyChangedEventHandler PropertyChanged;

        public string PlainText
        {
            get { return _plainText; }
            set
            {
                _plainText = value;
                OnPropertyChanged(nameof(PlainText));
                OnPropertyChanged(nameof(TextSize));
            }
        }

        public string CipherText
        {
            get { return _cipherText; }
            set
            {
                _cipherText = value;
                OnPropertyChanged(nameof(CipherText));
            }
        }

        public string Key
        {
            get { return _key; }
            set
            {
                _key = value;
                OnPropertyChanged(nameof(Key));
            }
        }
        public string TextSize
        {
            get { return "Длина сообщения: " + CipherText.Length; }

        }

        private string encryptionTime = "Время шифрования";
        public string EncryptionTime
        {
            get => encryptionTime;
            set
            {
                encryptionTime = value;
                OnPropertyChanged(nameof(EncryptionTime));
            }
        }

        private string decryptionTime = "Время дешифрования";
        public string DecryptionTime
        {
            get => decryptionTime;
            set
            {
                decryptionTime = value;
                OnPropertyChanged(nameof(DecryptionTime));
            }
        }


        public ICommand EncryptCommand { get; }
        public ICommand DecryptCommand { get; }

        public AESViewModel()
        {
            EncryptCommand = new RelayCommand(Encrypt);
            DecryptCommand = new RelayCommand(Decrypt);


            using (var rng = new System.Security.Cryptography.RNGCryptoServiceProvider())
            {
                rng.GetBytes(IV);
            }
        }

        private void Encrypt()
        {
            try
            {
                CipherText = AesEncryptor.Encrypt(PlainText, Key);
                EncryptionTime = AesEncryptor.GetEncriptionTime();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Ошибка: " + ex.Message, "Ошибка", MessageBoxButton.OK, MessageBoxImage.Error);

                // Handle exception
            }
        }

        private void Decrypt()
        {
            try
            {
                PlainText = AesEncryptor.Decrypt(CipherText, Key);
                DecryptionTime = AesEncryptor.GetDecriptionTime();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Ошибка: " + ex.Message, "Ошибка", MessageBoxButton.OK, MessageBoxImage.Error);

                // Handle exception
            }
        }

        private void OnPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }


        public ICommand SaveCipherToFileCommand => new RelayCommand(SaveToFileCipher);

        private void SaveToFileCipher()
        {
            var dialog = new SaveFileDialog();
            dialog.Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*";

            if (dialog.ShowDialog() == true)
            {
                using (var writer = new StreamWriter(dialog.FileName))
                {
                    writer.Write(this.CipherText);
                }
            }
        }


        public ICommand SaveToFileCommand => new RelayCommand(SaveToFile);

        private void SaveToFile()
        {
            var dialog = new SaveFileDialog();
            dialog.Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*";

            if (dialog.ShowDialog() == true)
            {
                using (var writer = new StreamWriter(dialog.FileName))
                {
                    writer.Write(this.PlainText);
                }
            }
        }

        public ICommand OpenFileCommand => new RelayCommand(() =>
        {
            var dialog = new OpenFileDialog();
            dialog.Filter = "Text files (*.txt)|*.txt";
            if (dialog.ShowDialog() == true)
            {
                var text = File.ReadAllText(dialog.FileName);
                PlainText = text;
            }
        });

        public ICommand OpenCipherFileCommand => new RelayCommand(() =>
        {
            var dialog = new OpenFileDialog();
            dialog.Filter = "Text files (*.txt)|*.txt";
            if (dialog.ShowDialog() == true)
            {
                var text = File.ReadAllText(dialog.FileName);
                CipherText = text;
            }
        });


        public ICommand ClearMsgCommand => new RelayCommand(() =>
        {
            PlainText = "";
        });
        public ICommand ClearCipherCommand => new RelayCommand(() =>
        {
            CipherText = "";
        });
    }
}
