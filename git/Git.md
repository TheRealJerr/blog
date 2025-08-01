以下是企业级 Git 常见操作的总结，涵盖团队协作、代码管理、分支策略和高效工作流的关键点：

---

### **1. 分支管理策略**
- **Git Flow**  
  - `main`/`master`：生产环境代码（仅允许合并）  
  - `develop`：集成测试分支  
  - `feature/*`：功能开发分支（从 `develop` 切出）  
  - `release/*`：预发布分支（用于测试）  
  - `hotfix/*`：紧急修复分支（从 `main` 切出）  
  ```bash
  git checkout -b feature/xxx develop  # 创建功能分支
  ```

- **Trunk-Based Development**（适合持续交付）  
  - 直接向 `main` 提交小批量代码，通过频繁集成减少冲突。

---

### **2. 代码提交规范**
- **Commit Message 格式**（如 [Conventional Commits](https://www.conventionalcommits.org/)）  
  ```
  feat(module): 添加登录功能  
  fix(api): 修复用户列表接口500错误  
  docs: 更新README  
  ```
- **原子性提交**：每个提交只解决一个问题，避免大杂烩。

---

### **3. 代码审查（Code Review）**
- **Pull Request (PR) / Merge Request (MR)**  
  - 通过 GitHub/GitLab 发起 PR，关联任务（如 Jira Issue ID）。  
  - 使用 `git push origin feature/xxx` 推送后，在平台创建 PR。  
- **Review 工具**：  
  - 行内评论、批准（Approval）、强制要求至少 1 人审核。

---

### **4. 远程仓库协作**
- **常用命令**  
  ```bash
  git clone <repo-url>                  # 克隆仓库
  git fetch --all                        # 获取远程更新（不合并）
  git pull origin develop               # 拉取并合并分支
  git push origin feature/xxx            # 推送分支
  git remote prune origin                # 清理本地已删除的远程分支
  ```
- **权限控制**：  
  - `main`/`develop` 分支保护：禁止直接 push，强制通过 PR。

---

### **5. 解决冲突与同步**
- **Rebase 代替 Merge**（保持提交历史线性）  
  ```bash
  git checkout feature/xxx
  git rebase develop     # 将 develop 最新更改应用到当前分支
  git rebase -i HEAD~3   # 交互式合并/修改提交历史
  ```
- **处理冲突**：  
  - 手动解决冲突后 `git add`，然后 `git rebase --continue`。

---

### **6. 版本发布与标签**
- **打标签（Tag）**  
  ```bash
  git tag -a v1.0.0 -m "正式版1.0.0"  # 创建标签
  git push origin v1.0.0               # 推送标签
  ```
- **回滚操作**：  
  ```bash
  git revert <commit-id>    # 生成一个反向提交（推荐团队协作）
  git reset --hard <commit> # 强制回退（谨慎使用！）
  ```

---

### **7. 子模块与大文件管理**
- **Git Submodule**（管理依赖仓库）  
  ```bash
  git submodule add <repo-url> <path>
  git submodule update --init --recursive
  ```
- **Git LFS**（大文件存储）  
  ```bash
  git lfs track "*.psd"      # 跟踪大文件
  git add .gitattributes
  ```

---

### **8. 企业级工具集成**
- **CI/CD 流水线**：  
  - 通过 `.gitlab-ci.yml` 或 GitHub Actions 自动构建、测试、部署。  
- **钩子（Hooks）**：  
  - 预提交检查（如 `pre-commit` 检查代码格式）。  
  - 服务端钩子（如 `pre-receive` 检查提交规范）。

---

### **9. 安全与审计**
- **SSH 密钥管理**：限制部署密钥权限。  
- **审计日志**：定期检查 `git log` 和平台操作记录。

---

### **10. 常见问题处理**
- **误提交敏感信息**：  
  ```bash
  git filter-repo --force --invert-paths --path passwords.txt  # 从历史中彻底删除文件
  ```
- **恢复丢失代码**：  
  ```bash
  git reflog                  # 查找丢失的 commit
  git cherry-pick <commit-id> # 应用特定提交
  ```

---

通过规范化的流程和工具链集成，企业可以确保 Git 高效、安全地支持团队协作。建议结合具体平台（如 GitHub/GitLab/Bitbucket）的权限管理和自动化功能进一步优化。