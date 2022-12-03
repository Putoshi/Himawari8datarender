using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO;
using System.Diagnostics;
using System.Threading;
using System.Threading.Tasks;
using System.Net;
using System.Net.Security;
using System.Security.Authentication;
using System.Security.Cryptography.X509Certificates;
using u32 = System.UInt32;
using s32 = System.Int32;
using f32 = System.Single;
namespace st_render5
{
    public class Funcs
    {
        public static void depress(string file)
        {
            Console.WriteLine("depressing " + file);
            Process d = new Process();
            d.StartInfo.FileName = "cmd.exe";
            d.StartInfo.UseShellExecute = false;
            d.StartInfo.CreateNoWindow = true;
            d.StartInfo.RedirectStandardError = true;
            d.StartInfo.RedirectStandardInput = true;
            d.StartInfo.RedirectStandardOutput = true;
            d.Start();
            d.StandardInput.WriteLine("7z e \"" + file + "\" &exit");
            d.StandardInput.AutoFlush = true;
            //Console.WriteLine(d.StandardOutput.ReadToEnd());
            d.WaitForExit();
            d.Close();
            d.Dispose();
            Console.WriteLine("depressed");
        }
        public static int download(string url, string file)
        {
            WebClient d = new WebClient();
            try
            {
                d.DownloadFile(url, file);
            }
            catch (Exception e)
            {
                d.Dispose();
                return -1;
            }
            d.Dispose();
            return 0;
        }
        public static int ToInt(string input)
        {
            int output = 0;
            for (int p = 0; p < input.Length; p++)
            {
                output += ToThePower(10, input.Length - p - 1) * ToIntbit(input[p]);
            }
            return output;

        }
        public static byte ToIntbit(char input)
        {
            byte output = 0;
            switch (input)
            {
                case ' ': { output = 0; break; }
                case '0': { output = 0; break; }
                case '1': { output = 1; break; }
                case '2': { output = 2; break; }
                case '3': { output = 3; break; }
                case '4': { output = 4; break; }
                case '5': { output = 5; break; }
                case '6': { output = 6; break; }
                case '7': { output = 7; break; }
                case '8': { output = 8; break; }
                case '9': { output = 9; break; }
                default: { output = 0; break; }
            }
            return output;

        }
        public static int ToThePower(int b, int index)
        {
            int output = 1;
            while (index != 0)
            {
                output *= b;
                index--;
            }
            return output;
        }
    }

}