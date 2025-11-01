from django.urls import path, include
from rest_framework.routers import DefaultRouter
from .views import TaskViewSet, NoteViewSet

router = DefaultRouter()
router.register(r'tasks', TaskViewSet, basename='task')
router.register(r'notes', NoteViewSet, basename='note')

urlpatterns = [
    path('', include(router.urls)),
]