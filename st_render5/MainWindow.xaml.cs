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

namespace st_render5
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            string[] a = Environment.GetCommandLineArgs();
            st_render5.InputArgs args = InputArgs.SplitInput(a);
            Console.WriteLine("st_renderV5 by 031");
            Console.WriteLine(args.op);

            switch (args.op)
            {
                case 1: { strender.RenderHSD(args.path, args.filename, args.color, args.outputpic); Environment.Exit(0); break; }
                case 2: { strender.RenderATyphoonFLDK("08","WVNRL"); break; }
            }

            
        }
    }
}
