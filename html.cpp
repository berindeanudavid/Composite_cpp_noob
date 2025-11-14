#include <bits/stdc++.h>

class Html{
    public:
        virtual void html_write(int indent){
            std::cout << "Default html write called\n";
        }
        std::string applyIndent(std::string arg0, int indent){
            std::string output;
            for(int i=0; i<indent; i++){
                output=output+" ";
            }
            output=output+arg0;
            return output;
        }
};

class Text : public Html{
    public:
        std::string text;
        Text(){
            text="";
            std::cout << "WARNING: Default Constructor called for Text.\n";
        }
        Text(std::string arg0){
            text=arg0;
        }
        void html_write(int indent) override{
            std::cout << applyIndent(text, indent) << "\n";
        }
};

class Paragraph : public Html{
    public:
        std::string text;
        Paragraph(){
            text="";
            std::cout << "WARNING: Default Constructor called for Paragraph.\n";
        }
        Paragraph(std::string arg0){
            text=arg0;
        }
        void html_write(int indent) override{
            std::cout << applyIndent("<p>\n", indent) << applyIndent(text, indent) << "\n" << applyIndent("</p>\n", indent);
        }
};

class Div : public Html{
    public:
        std::list<Html*> html_elements;
        void add_html(Html* arg0_ptr){
            html_elements.push_back(arg0_ptr);
        }
        void html_write(int indent) override{
            int current_indent=indent;
            std::cout << applyIndent("<div>\n", current_indent);
            current_indent=current_indent+4;
            for(Html* ptr : html_elements){
                ptr->html_write(current_indent);
            }
            current_indent=current_indent-4;
            std::cout << applyIndent("</div>\n",current_indent);
        }
};

class HtmlFile{
    public:
        std::list<Html*> all_html_elements;
        void load(){
            Text text1("body text");
            Html* text1_ptr=&text1;
            Div div1; // empty div
            Html* div1_ptr=&div1;
            Text text2("text inside a div");
            Html* text2_ptr=&text2;
            Paragraph p1("paragraph inside a div");
            Html* p1_ptr=&p1;
            Text text3("text inside a div inside a div");
            Html* text3_ptr=&text3;
            Div div2;
            div2.add_html(text2_ptr);
            div2.add_html(p1_ptr);
            Div div3;
            div3.add_html(text3_ptr);
            Html* div3_ptr=&div3;
            div2.add_html(div3_ptr);
            Html* div2_ptr=&div2;
            all_html_elements.push_back(text1_ptr);
            all_html_elements.push_back(div1_ptr);
            all_html_elements.push_back(p1_ptr);
            all_html_elements.push_back(div2_ptr);
            std::cout << "\n<!DOCTYPE html>\n";
            std::cout << "<html>\n";
            std::cout << "<head>\n";
            std::cout << "<title>This is Composition</title>\n";
            std::cout << "</head>\n";
            std::cout << "    <body>\n";
            for(Html* ptr : all_html_elements){
                ptr->html_write(8);
            }
            std::cout << "    </body>\n";
            std::cout << "</html>\n\n";
        }
};

int main(){
    HtmlFile file;
    file.load();
    return 0;
}

/*
OUTPUT:

<!DOCTYPE html>
<html>
<head>
<title>This is Composition</title>
</head>
    <body>
        body text
        <div>
        </div>
        <p>
        paragraph inside a div
        </p>
        <div>
            text inside a div
            <p>
            paragraph inside a div
            </p>
            <div>
                text inside a div inside a div
            </div>
        </div>
    </body>
</html>
*/