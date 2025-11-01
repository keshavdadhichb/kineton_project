# Kineton: Task & Note Management API

This project is a backend application built with Django and fully containerized using Docker. It provides a secure, multi-user RESTful API for managing tasks and notes, complete with user authentication, file upload capabilities, and relational data linking.

The entire application stack (Django web server + PostgreSQL database) is provisioned using Docker Compose for seamless, one-command setup and execution.

---

## Core Features

* **User Authentication:** Secure user registration, login (including Google OAuth), and logout.
* **Task Management:** Full CRUD (Create, Read, Update, Delete) operations for user-specific tasks.
* **Note Management:** Full CRUD operations for notes, with support for file uploads (PDF, TXT, DOCX).
* **Data Linking:** Ability to associate notes with specific tasks for organization.
* **Security:** Endpoints are secured, ensuring users can only access and manage their own data.
* **Containerization:** The application and its PostgreSQL database run in isolated Docker containers.
* **API Documentation:** Live, interactive API documentation is automatically generated with Swagger (OpenAPI).

---

## Technology Stack

* Django & Django REST Framework
* PostgreSQL
* Docker & Docker Compose
* `dj-rest-auth` & `django-allauth` for authentication
* `drf-spectacular` for OpenAPI/Swagger documentation

---

## Getting Started

### Prerequisites

* Docker
* Docker Compose

### Installation & Execution

1.  **Clone the Repository**
    ```bash
    git clone [your-github-repository-url]
    cd [repository-name]
    ```

2.  **Configure Environment**
    Create a `.env` file in the project root. This is required for the application to run.
    ```env
    # Required for Google OAuth
    GOOGLE_CLIENT_ID="your-google-client-id"
    GOOGLE_CLIENT_SECRET="your-google-client-secret"
    
    # Required for creating an admin user on first run
    DJANGO_SUPERUSER_USERNAME="admin"
    DJANGO_SUPERUSER_EMAIL="admin@example.com"
    DJANGO_SUPERUSER_PASSWORD="a-strong-password"
    ```

3.  **Build and Run**
    The following command will build the Docker images, start the containers, and run the database migrations.
    ```bash
    docker compose up --build
    ```
    The application will be running at `http://localhost:8000`.

---

## Endpoints & Documentation

Once the application is running, the following endpoints are available:

* **Frontend Dashboard:** `http://localhost:8000/`
* **Django Admin:** `http://localhost:8000/admin/`
    * (Login with the `DJANGO_SUPERUSER` credentials set in your `.env` file)

### API Documentation (Swagger UI)

A complete, interactive API documentation page is available via Swagger. This allows for testing all API endpoints directly from the browser.

* **Swagger Docs:** `http://localhost:8000/api/docs/`
* **API Schema:** `http://localhost:8000/api/schema/`

---

## Running Unit Tests

The project includes a suite of unit tests for key API endpoints, focusing on business logic and security (e.g., ensuring users cannot access another user's data).

To run the tests, ensure the containers are running and execute the following command in your terminal:

```bash
docker compose exec web python manage.py test