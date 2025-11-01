from django.contrib.auth.models import User
from rest_framework.test import APITestCase
from rest_framework import status
from .models import Task

class TaskAPITests(APITestCase):
    
    def setUp(self):
        # Create two distinct users for testing
        self.userA = User.objects.create_user(
            username='userA', 
            password='password123'
        )
        self.userB = User.objects.create_user(
            username='userB', 
            password='password123'
        )

        # Create a task that belongs only to userA
        self.taskA = Task.objects.create(
            user=self.userA, 
            title='User A Task'
        )

    def test_authenticated_user_can_create_task(self):
        """
        Ensure an authenticated user can create a new task.
        """
        # Authenticate as userA
        self.client.force_authenticate(user=self.userA)
        
        url = '/api/v1/tasks/'
        data = {'title': 'New Task for User A'}
        
        response = self.client.post(url, data, format='json')
        
        self.assertEqual(response.status_code, status.HTTP_201_CREATED)
        self.assertEqual(Task.objects.count(), 2) # (self.taskA + new one)
        self.assertEqual(Task.objects.latest('id').title, 'New Task for User A')

    def test_unauthenticated_user_cannot_access_tasks(self):
        """
        Ensure an unauthenticated (anonymous) user receives a 401 error.
        """
        # Note: We do not authenticate the client
        url = '/api/v1/tasks/'
        response = self.client.get(url)
        
        self.assertEqual(response.status_code, status.HTTP_401_UNAUTHORIZED)

    def test_user_can_only_see_their_own_tasks(self):
        """
        Ensure userA can see their tasks, but not userB's tasks.
        """
        # Authenticate as userA
        self.client.force_authenticate(user=self.userA)
        
        url = '/api/v1/tasks/'
        response = self.client.get(url)
        
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        # Check that the API returned one task
        self.assertEqual(response.data['count'], 1) 
        # Check that the task title matches userA's task
        self.assertEqual(response.data['results'][0]['title'], self.taskA.title)

    def test_user_cannot_access_another_users_task_detail(self):
        """
        Ensure userB receives a 404 when trying to access userA's task by its ID.
        """
        # Authenticate as userB
        self.client.force_authenticate(user=self.userB)
        
        # URL for userA's task
        url = f'/api/v1/tasks/{self.taskA.pk}/'
        response = self.client.get(url)
        
        # This is the key security test.
        self.assertEqual(response.status_code, status.HTTP_404_NOT_FOUND)

    def test_user_cannot_update_another_users_task(self):
        """
        Ensure userB cannot update userA's task.
        """
        # Authenticate as userB
        self.client.force_authenticate(user=self.userB)
        
        url = f'/api/v1/tasks/{self.taskA.pk}/'
        data = {'title': 'Hacked by User B', 'completed': True}
        
        response = self.client.put(url, data, format='json')
        
        self.assertEqual(response.status_code, status.HTTP_404_NOT_FOUND)