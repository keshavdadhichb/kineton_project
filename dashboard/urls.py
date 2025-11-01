from django.urls import path
from .views import (
    dashboard_view,
    task_edit_view,
    task_delete_view,
    task_toggle_complete_view
)

urlpatterns = [
    path('', dashboard_view, name='dashboard'),
    path('task/<int:pk>/edit/', task_edit_view, name='task_edit'),
    path('task/<int:pk>/delete/', task_delete_view, name='task_delete'),
    path('task/<int:pk>/toggle/', task_toggle_complete_view, name='task_toggle'),
]