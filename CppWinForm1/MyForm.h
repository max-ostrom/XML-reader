#pragma once

namespace CppWinForm1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Xml;
	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

			loadFile->Location = Point(40, 20);
			convert->Location = Point(150, 20);
			textField->Location = Point(40, 80);

			loadFile->Name = L"LoadFileButton";

			loadFile->Size = System::Drawing::Size(100, 40);
			convert->Size = System::Drawing::Size(100, 40);
			textField->Size = System::Drawing::Size(200, 150);

			convert->Text = "Convert";
			loadFile->Text = "Load File";

			loadFile->Click += gcnew EventHandler(this, &MyForm::LoadFileButton_click);
			convert->Click += gcnew System::EventHandler(this, &MyForm::ConvertButton_click);

			this->Controls->Add(loadFile);
			this->Controls->Add(textField);
			this->Controls->Add(convert);


		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
		void ConvertButton_click(Object^ sender, EventArgs^ e) 
		{
			textField->Text = "";
			XmlTextReader^ reader = gcnew XmlTextReader("1.xml");
			while (reader->ReadToFollowing("catalog"))
			{
				if (reader->ReadToDescendant("book"))
				{
					int pointCount = 0;
					do
					{
						pointCount++;//Увеличиваем счетчик числа найденных точек

						String^ author;
						String^ title;
						String^ Type;

						//Считываем атрибут
						Type = reader->GetAttribute("id");

						//Внутри точки есть тэги <x> и <y>.
						//Вытащим все тэги в отдельное дерево
						XmlReader^ inner = reader->ReadSubtree();

						//И пробежимся по всем внутренностям данного поддерева точки
						while (inner->Read())
						{
							//Если текущий элемент это открывающий тэг <x>,
							//то следующий элемент - это текст внутри тэга <x></x>
							if ((inner->Name == "author") && (inner->NodeType == XmlNodeType::Element))
							{
								//Поэтому считываем еще один элемент и этот элемент то, что нам нужно
								inner->Read();
								author = inner->Value;
							}
							//Если текущий элемент это открывающий тэг <y>,
							//то следующий элемент - это текст внутри тэга <y></y>
							if ((inner->Name == "title") && (inner->NodeType == XmlNodeType::Element))
							{
								//Поэтому считываем еще один элемент и этот элемент то, что нам нужно
								inner->Read();
								title = inner->Value;
							}
						}

						//Выведем считанную информацию 
						textField->Text += "Книга №" + pointCount.ToString() + "\r\n";
						textField->Text += "  ID = " + Type + "\r\n";
						textField->Text += "  Author " + author + "\r\n";
						textField->Text += "  Title " + title + "\r\n\n";

					} while (reader->ReadToNextSibling("book"));
				}
			}
		}
		void LoadFileButton_click(Object^ sender, EventArgs^ e)
		{
			textField->Text = "";
			XmlTextReader^ reader = gcnew XmlTextReader("1.xml");
			while (reader->Read())
			{
				switch (reader->NodeType)
				{
				case XmlNodeType::Element:
				{
					textField->Text += "<" + reader->Name + " ";
					while (reader->MoveToNextAttribute())
						textField->Text += reader->Name + " = \"" + reader->Value + "\" ";
					textField->Text += ">\r\n";
					break;
				}
				case XmlNodeType::Text:
				{
					textField->Text +="    " + reader->Value + "\r\n";
					break;
				}
				case XmlNodeType::EndElement:
				{
					textField->Text +="</" + reader->Name + ">\r\n";
					break;
				}
				}
				
			}
		}
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
		Button^ loadFile = gcnew Button();
		Button^ convert = gcnew Button();
		RichTextBox^ textField = gcnew RichTextBox();
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = gcnew System::ComponentModel::Container();
			this->Size = System::Drawing::Size(300, 300);
			this->Text = L"MyForm";
			this->Padding = System::Windows::Forms::Padding(0);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		}
#pragma endregion
	};
}
