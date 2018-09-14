#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

class LegalText
{
public:
    LegalText(std::string src, std::string baseSrcDir = "./", std::string baseDstDir = "./")
        : m_baseSrcDir(baseSrcDir), m_baseDstDir(baseDstDir)
        {
            std::size_t found = src.rfind("/");

            if (found != std::string::npos)
            {
                m_srcFile = src.substr(found + 1, src.length());
                m_srcDir = src.substr(0, found + 1);
                std::cout << src << ", " << m_srcFile << ", " << m_srcDir << std::endl;
            } 
            else{
                m_srcFile = src;
            }
        }
    std::string getFullSrcPath() { return m_baseSrcDir + m_srcDir + m_srcFile; }
    std::string getFullDstPath() { return getFullDstDirPath() + m_srcFile; }
    std::string getFullDstDirPath()
    {
        std::string path = m_baseDstDir;
        return path.append("/out/").append(m_srcDir);
    }
private:
    std::string m_srcFile;
    std::string m_srcDir;
    std::string m_baseSrcDir;
    std::string m_baseDstDir;
};


#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

class FileTool
{
public:
    FileTool(std::string file)
        : m_file(file) {}
    bool isExist();
    bool isDirectory();
    bool isFile();
    std::vector<std::string> getFiles();

private:
    std::string m_file;
};

bool FileTool::isExist()
{
    int ret = access(m_file.c_str(), 0);
    if (0 == ret)
        return true;
    return false;
}

bool FileTool::isDirectory()
{
    struct stat buf = {0};

    if (!isExist())
        return false;

    if (lstat(m_file.c_str(), &buf) < 0)
        return false;

    return S_ISDIR(buf.st_mode) ? true : false;
}

bool FileTool::isFile()
{
    struct stat buf = {0};

    if (!isExist())
        return false;

    if (lstat(m_file.c_str(), &buf) < 0)
        return false;

    return S_ISREG(buf.st_mode) ? true : false;
}

std::vector<std::string> FileTool::getFiles()
{
    std::vector<std::string> files;

    if (isDirectory())
    {
        DIR *dp;
        struct dirent *ent;

        dp = opendir(m_file.c_str());
        if (NULL != dp)
        {
            while (NULL != (ent = readdir(dp)))
            {
                struct stat buf = {0};

                lstat(ent->d_name, &buf);
                if (S_ISDIR(buf.st_mode))
                    continue;
                
                std::string dir = m_file;
                files.push_back(dir.append("/").append(ent->d_name));
            }
        }

    }
    else
    {
        std::cout << "not a directory" << std::endl;
    }

    return files;
}

class TextBuilder
{
public:
    TextBuilder(std::string file, std::string baseSrcDir = "./", std::string baseDstDir = "./")
        : m_listFile(file), m_baseSrcDir(baseSrcDir), m_baseDstDir(baseDstDir) {}
    void parse();
    std::vector<LegalText> getLegalTextFiles() { return m_textList; }

private:
    std::vector<LegalText> m_textList;
    std::vector<std::string> aaa;

    std::string m_listFile;
    std::string m_baseSrcDir;
    std::string m_baseDstDir;
};

void TextBuilder::parse()
{
    std::string file;

    std::ifstream in(m_listFile.c_str());
    if (in.is_open()) {
        
        m_textList.clear();

        while (in >> file) {
            std::cout << file;
            FileTool ft(file);
            if (ft.isFile()) {
                std::cout << ", file, push back " << file << std::endl;
                m_textList.push_back(LegalText("hello"));
            } else {
                std::cout << ", not a file" << std::endl;

                std::vector<std::string>::iterator iter;
                std::vector<std::string> files = ft.getFiles();
                for (iter = files.begin(); iter != files.end(); ++iter)
                    m_textList.push_back(LegalText(*iter));
            }
        }
    } else {
        std::cout << "failed to open " << m_listFile << std::endl;
    }
}

int main(void)
{
    TextBuilder tb(std::string("list.txt")); 
    tb.parse();

    std::vector<LegalText>::iterator iter;
    std::vector<LegalText> files = tb.getLegalTextFiles();
    for (iter = files.begin(); iter != files.end(); ++iter)
    {
        std::cout << iter->getFullSrcPath() << std::endl;
        std::cout << iter->getFullDstPath() << std::endl;
    }

#if 0
    LegalText lt("files_a/a_1.txt");
    std::cout << lt.getFullSrcPath() << std::endl;
    std::cout << lt.getFullDstPath() << std::endl;
    std::cout << lt.getFullDstDirPath() << std::endl;

    FileTool ft("files_a");
    std::cout << ft.isExist() << std::endl;
    std::cout << ft.isDirectory() << std::endl;
    std::cout << ft.isFile() << std::endl;

    std::vector<std::string>::iterator iter;
    std::vector<std::string> files = ft.getFiles();

    for (iter = files.begin(); iter != files.end(); ++iter)
        std::cout << *iter << std::endl;
#endif

    return 0;
}
